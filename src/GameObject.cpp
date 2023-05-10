#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
int temp = 0;

GameObject::GameObject(int x, int y){
    xpos = x;
    ypos = y;
    xvel = 0;
    yvel = 0;

    srcRect.h = 32;
    srcRect.w = 24 * 5;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = 24;
    destRect.h = 32;

    x_map = 0;
    y_map = 0;

    onGround = false;
    left = space = -1;
    right = 0;
    frame = 0;
    dead = false;
    flip = SDL_FLIP_NONE;
    dead_ani = 8;
    playing = true;
    won = false;

    for (int i = 0; i < 6; i++) {
        marioRect[i].x = i * 24;
        marioRect[i].y = 0;
        marioRect[i].w = 24;
        marioRect[i].h = 32;
    }
}



GameObject::~GameObject(){};

void GameObject::Update(){
    destRect.h = srcRect.h;
    destRect.w = 24;
    destRect.x = xpos - x_map;
    destRect.y = ypos - y_map;
    if (xpos >= 6216) {
        won = true;
    }
}

void GameObject::InputHandle(SDL_Event &e){
    if (!won) {
        if (e.type == SDL_KEYDOWN  && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    yvel -= speedY * 8; break;
                case SDLK_DOWN:
                    yvel += speedY; break;
                case SDLK_LEFT:
                    xvel -= speedX; if (!Game::paused) {left = 1; right = -1;}; break;
                case SDLK_RIGHT:
                    xvel += speedX; if (!Game::paused) {left = -1; right = 1;}; break;
                case SDLK_SPACE:
                    {if (onGround) space = 16; if (dead) space = 0; break;}
            }
        }
        else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    yvel += speedY * 8; break;
                case SDLK_DOWN:
                    yvel -= speedY; break;
                case SDLK_LEFT:
                    xvel += speedX; break;
                case SDLK_RIGHT:
                    xvel -= speedX; break;
                case SDLK_SPACE:
                    break;
            }
        }
    }
    else {
        xvel = 0;
        yvel = 0;
    }
}

void GameObject::Render(){
    if (!dead) {
        dead_ani = 8;
        SDL_Texture* object = TextureManager::LoadTexture("assets/images/marioall.png");
        if (xvel != 0 && onGround) {
            if (!Game::paused){
                if (xvel > 0) flip = SDL_FLIP_NONE;
                else flip = SDL_FLIP_HORIZONTAL;
            }
        }

        if (_frame >= 4 && onGround) _frame = 0;

        if (!onGround && xvel != 0) {
            _frame = 4;
            if (!Game::paused) {
                if (xvel > 0) flip = SDL_FLIP_NONE;
                else flip = SDL_FLIP_HORIZONTAL;
            }
        }

        SDL_RenderCopyEx(Game::renderer, object, &marioRect[_frame], &destRect, 0, NULL, flip);
        SDL_DestroyTexture(object);
        object = NULL;
    }
    else {
        xvel = 0;
        _frame = 5;
        space = 0;
        SDL_Texture* object = TextureManager::LoadTexture("assets/images/marioall.png");
        SDL_RenderCopyEx(Game::renderer, object, &marioRect[_frame], &destRect, 0, NULL, flip);
        SDL_DestroyTexture(object);
        object = NULL;
        if (!Game::paused) {
            if (dead_ani > 0) {
                ypos -= 16;
                dead_ani--;
            }
            ypos += 4;
            if (ypos >= Game::SCREEN_HEIGHT + 64) {
                dead = false;
                playing = false;
            }
        }
    }
}

void GameObject::Move(){
    xpos += xvel;
    if (xpos < 0 || xpos + destRect.w > 7120 || CheckX()) xpos -= xvel;
    if (dead) xvel = 0;
}

SDL_Rect GameObject::GetRect(){
    return destRect;
}

void GameObject::ApplyAnimation(){
    if (!won) {
        if (xvel != 0 && onGround) {
            if (frame >= 4.0) frame = 0;
            frame += 0.25;

            _frame = (int(frame) + 1) % 4;
        }
        else if (xvel == 0 && onGround) {_frame = 0; frame = 0;}
        else if (!onGround) _frame = 4;
    }
    else {
        if (frame >= 4.0) frame = 0;
        frame += 0.25;
        _frame = (int(frame) + 1) % 4;
    }
}


bool GameObject::CheckX(){
    int x1, x2, y1, y2;
    x1 = xpos / 32;
    x2 = (xpos + destRect.w - 1) / 32;

    y1 = ypos / 32;
    y2 = (ypos + destRect.h - 1) / 32;

    if (xvel > 0) {
        if (Map::game_map[y1][x2] != 0 || Map::game_map[y2][x2] != 0) {
            return true;
        }
    }
    else if (xvel < 0) {
        if (Map::game_map[y1][x1] != 0 || Map::game_map[y2][x1] != 0) {
            return true;
        }
    }

    return false;
}

bool GameObject::CheckY(){
    int x1, x2, y1, y2;
    x1 = xpos / 32;
    x2 = (xpos + destRect.w - 1) / 32;

    y1 = ypos / 32;
    y2 = (ypos + destRect.h - 1) / 32;

    if (yvel > 0) {
        if (Map::game_map[y2][x1] != 0 || Map::game_map[y2][x2] != 0) {
            onGround = true;
            return true;
        }
    }
    else if (yvel < 0) {
        if (Map::game_map[y1][x1] != 0 || Map::game_map[y1][x2] != 0) {
            return true;
        }
    }
    return false;
}


void GameObject::Physics(){
    if (space > 0) {
        ypos -= 16;
        if (ypos < 0) {
            ypos += 32;
            space = 0;
        }
        else space --;
    }

    ypos += speedY * 2;

    int x1, x2, y1, y2;
    x1 = xpos / 32;
    x2 = (xpos + destRect.w - 1) / 32;

    y1 = ypos / 32;
    y2 = (ypos + destRect.h - 1) / 32;
        {
            if (Map::game_map[y2][x1] != 0 || Map::game_map[y2][x2] != 0) {
                ypos -= speedY * 2;

                onGround = true;
                space = 0;
            }
            else onGround = false;

        {
            if (Map::game_map[y1][x1] != 0 || Map::game_map[y1][x2] != 0) {
                if (Map::game_map[y1][x1] == 18) {
                    Map::game_map[y1][x1] = 0;
                    
                }
                if (Map::game_map[y1][x2] == 18) {
                    Map::game_map[y1][x2] = 0;
                }
                ypos += (16 - speedY * 2);
                space = 0;
            }
        }
    }

}


void GameObject::CenterMapIndex(){
    x_map = xpos - (Game::SCREEN_WIDTH / 2);
    if (x_map < 0) x_map = 0;
    else if (x_map + Game::SCREEN_WIDTH >= 7168) x_map = 7168 - Game::SCREEN_WIDTH;
}


bool GameObject::DeadCheck(SDL_Rect &enemyRect){
    return TextureManager::PlayerCollisionChecker(destRect, enemyRect);
}

int GameObject::GetX(){
    return xpos;
}

int GameObject::GetY(){
    return ypos;
}

bool GameObject::Jumped(SDL_Rect &enemyRect){
    if (ypos <= enemyRect.y - 1) return true;
    else return false;
}

void GameObject::Bounce(){
    space = 16;
}
void GameObject::SetPos(){
    xpos = 96;
    ypos = 96;
}

void GameObject::win(){
    if (xpos <= 6880){
        if (ypos == 384) xpos += 2;
        if (ypos < 384) {
            ypos += 4;
            _frame = 4;
        }
        _time = SDL_GetTicks();
    }
    else {
        _frame = 0;
    }

    if (SDL_GetTicks() - _time >= 500) endtime = true;

    SDL_Texture* object = TextureManager::LoadTexture("assets/images/marioall.png");
    SDL_RenderCopyEx(Game::renderer, object, &marioRect[_frame], &destRect, 0, NULL, SDL_FLIP_NONE);
    SDL_DestroyTexture(object);
    object = NULL;
}

void GameObject::ResetVel(){
    xvel = 0;
}