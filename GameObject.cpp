#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
int temp = 0;

GameObject::GameObject(const char* file, int x, int y){
    //objectTexture.push_back(TextureManager::LoadTexture(file));
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
    dead_ani = 5;
    life = 3;
    bounce = 8;
    playing = true;
    won = false;
}

GameObject::~GameObject(){};

void GameObject::Update(){
    destRect.h = srcRect.h;
    destRect.w = 24;
    destRect.x = xpos - x_map;
    destRect.y = ypos - y_map;
    if (xpos > 6152) won = true;

    // destRect.x = xpos - x_map;
    // destRect.y = ypos - y_map;
};

void GameObject::Render(){


    // SDL_Texture* object = TextureManager::LoadTexture("assets/marioall.png");

    // SDL_Texture* fobject = TextureManager::LoadTexture("assets/fmarioall.png");

    // if (right >=0) if (xvel >=0) SDL_RenderCopy(Game::renderer, object, &marioRect[_frame], &destRect);
    // if (left >=0) if (xvel <= 0) SDL_RenderCopy(Game::renderer, fobject, &marioRect[_frame], &destRect);
    // SDL_DestroyTexture(object);
    // SDL_DestroyTexture(fobject);



    //SDL_RenderCopy(Game::renderer, objectTexture[0], &marioRect[_frame], &destRect);


//    if (right >=0) if (xvel >=0) SDL_RenderCopy(Game::renderer, objectTexture, &marioRect[_frame], &destRect);
    //if (left >=0) if (xvel <= 0) SDL_RenderCopy(Game::renderer, fobjectTexture, &marioRect[_frame], &destRect);
    //SDL_DestroyTexture(objectTexture);
    //SDL_DestroyTexture(fobjectTexture);
    //objectTexture = NULL;
    //std::cout<< objectTexture << std::endl;
}

void GameObject::InputHandle(SDL_Event &e){

    if (e.type == SDL_KEYDOWN  && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                yvel -= speedY * 8; break;
            case SDLK_DOWN:
                yvel += speedY; break;
            case SDLK_LEFT:
                xvel -= speedX; left = 1; right = -1; break;
            case SDLK_RIGHT:
                xvel += speedX; left = -1; right = 1; break;
            case SDLK_SPACE:
                {if (onGround) space = 16; break;}
        }
    }
    else if (e.type == SDL_KEYUP){
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                yvel += speedY * 8; break;
            case SDLK_DOWN:
                yvel -= speedY; break;
            case SDLK_LEFT:
                xvel += speedX; break; // left = 0; right = -1; break;
            case SDLK_RIGHT:
                xvel -= speedX; break;// right = 0; left = -1; break;
            case SDLK_SPACE:
                break;
        }
    }


}


void GameObject::Move(){

    if (!dead) {
        SDL_Texture* object = TextureManager::LoadTexture("assets/marioall.png");
        if (xvel != 0 && onGround) {
            _frame++;
        if (xvel > 0) flip = SDL_FLIP_NONE;
        else flip = SDL_FLIP_HORIZONTAL;
        }

        if (_frame >= 4 && onGround) _frame = 0;

        if (!onGround && xvel != 0) {
            _frame = 4;
            if (xvel > 0) flip = SDL_FLIP_NONE;
            else flip = SDL_FLIP_HORIZONTAL;
        }



        SDL_RenderCopyEx(Game::renderer, object, &marioRect[_frame], &destRect, 0, NULL, flip);
        SDL_DestroyTexture(object);
        object = NULL;

        xpos += xvel;
        if (xpos < 0 || xpos + destRect.w > 7120 || CheckX()) xpos -= xvel;

        if (ypos < 0 || ypos + destRect.h > Game::SCREEN_HEIGHT || CheckY()) {
            ypos -= yvel;
        }
    std::cout << xpos << ' ' << ypos << std::endl;
    }
    else {
        _frame = 5;
        //if (space > 0) space = -1;;
        SDL_Texture* object = TextureManager::LoadTexture("assets/marioall.png");
        SDL_RenderCopyEx(Game::renderer, object, &marioRect[_frame], &destRect, 0, NULL, flip);
        SDL_DestroyTexture(object);
        object = NULL;
        if (dead_ani > 0) {
            ypos -= 32;
            dead_ani--;
        }

        //SDL_Delay(10);
        ypos += 1;
        if (ypos >= Game::SCREEN_HEIGHT + 64) {
            dead = false;
            //life--;
            dead_ani = 5;
            playing = false;
            xpos = 96;
            ypos = 96;
        }

    }

}
SDL_Rect GameObject::GetRect(){
    return destRect;
}

void GameObject::LoadAnimation(){
    for (int i = 0; i < 6; i++) {
        marioRect[i].x = i * 24;
        marioRect[i].y = 0;
        marioRect[i].w = 24;
        marioRect[i].h = 32;
    }
}

void GameObject::ApplyAnimation(){
    if (xvel != 0 && onGround) {
        if (frame >= 4.0) frame = 0;
        frame += 0.25;

        _frame = (int(frame) + 1) % 4;
    }
    else if (xvel == 0 && onGround) {_frame = 0; frame = 0;}
    else if (!onGround) _frame = 4;
}


bool GameObject::CheckX(){
    int x1, x2, y1, y2;
    x1 = xpos / 32;
    x2 = (xpos + destRect.w - 1) / 32;

    y1 = ypos / 32;
    y2 = (ypos + destRect.h - 1) / 32;

    if (xvel > 0) {
        if (Map::level_1[y1][x2] != 0 || Map::level_1[y2][x2] != 0) {
            return true;
        }
    }
    else if (xvel < 0) {
        if (Map::level_1[y1][x1] != 0 || Map::level_1[y2][x1] != 0) {
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
        if (Map::level_1[y2][x1] != 0 || Map::level_1[y2][x2] != 0) {
            onGround = true;
            return true;
        }
    }
    else if (yvel < 0) {
        if (Map::level_1[y1][x1] !=0 || Map::level_1[y1][x2] != 0) {
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
        if (Map::level_1[y2][x1] != 0 || Map::level_1[y2][x2] != 0) {
            ypos -= speedY * 2;
            onGround = true;
            space = 0;
        }
        else onGround = false;
    {
        if (Map::level_1[y1][x1] !=0 || Map::level_1[y1][x2] != 0) {
            ypos += 16;
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

void GameObject::win(){
//    for (int i = 0; i < 10; i++) {
//        xpos += 32;
//        //SDL_Delay(1);
//    }
}
