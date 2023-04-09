#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
GameObject::GameObject(const char* file, int x, int y){
    objectTexture = TextureManager::LoadTexture(file);
    xpos = x;
    ypos = y;
    xvel = 0;
    yvel = 0;
    srcRect.h = 32;
    srcRect.w = 24;
    srcRect.x = 0;
    srcRect.y = 0;
    x_map = 0;
    y_map = 0;
    onGround = false;
    space = -1;
}
void GameObject::Update(){

    destRect.h = srcRect.h;
    destRect.w = 24;
    destRect.x = xpos;
    destRect.y = ypos;
};

void GameObject::Render(){
    //GameObject::setCamera(destRect);
    //xp = xpos;
    destRect.x = xpos - x_map;
    destRect.y = ypos - y_map;
    SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);

}

void GameObject::InputHandle(SDL_Event &e){

    if (e.type == SDL_KEYDOWN  && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                yvel -= speedY * 8; break;
            case SDLK_DOWN:
                yvel += speedY; break;
            case SDLK_LEFT:
                xvel -= speedX; break;
            case SDLK_RIGHT:
                xvel += speedX; break;
            case SDLK_SPACE:
                if (onGround) space = 8; break;// yvel -= speedY * 8; break;
        }
    }
    else if (e.type == SDL_KEYUP){
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
                //yvel += speedY * 8;
                break;
        }
    }


}


void GameObject::Move(){
    xpos += xvel;
    if (xpos < 0 || xpos + destRect.w > 7120 || CheckX()) xpos -= xvel;
    ypos += yvel;
    //if (check) yvel -= speedY * 6;
    //if (yvel == speedY * 12) ypos -= yvel / 2;
    if (ypos < 0 || ypos + destRect.h > Game::SCREEN_HEIGHT || CheckY()) {
        ypos -= yvel;
    }


}
SDL_Rect GameObject::GetRect(){
    return destRect;
}

void GameObject::LoadAnimation(){
    for (int i = 0; i < 4; i++) {
        marioRect[i].x = i * 24;
        marioRect[i].y = 0;
        marioRect[i].w = 24;
        marioRect[i].h = 32;
    }



    DefaultTex = TextureManager::LoadTexture("assets/mario.png");
    Tex[0] = TextureManager::LoadTexture("assets/mario_move0.png");
    Tex[1] = TextureManager::LoadTexture("assets/mario_move0.png");
    Tex[2] = TextureManager::LoadTexture("assets/mario_move1.png");
    Tex[3] = TextureManager::LoadTexture("assets/mario_move1.png");
    Tex[4] = TextureManager::LoadTexture("assets/mario_move2.png");
    Tex[5] = TextureManager::LoadTexture("assets/mario_move2.png");

    fDefaultTex = TextureManager::LoadTexture("assets/fmario.png");
    fTex[0] = TextureManager::LoadTexture("assets/fmario_move0.png");
    fTex[1] = TextureManager::LoadTexture("assets/fmario_move0.png");
    fTex[2] = TextureManager::LoadTexture("assets/fmario_move1.png");
    fTex[3] = TextureManager::LoadTexture("assets/fmario_move1.png");
    fTex[4] = TextureManager::LoadTexture("assets/fmario_move2.png");
    fTex[5] = TextureManager::LoadTexture("assets/fmario_move2.png");

    JumpTex = TextureManager::LoadTexture("assets/mario_jump.png");
    fJumpTex = TextureManager::LoadTexture("assets/fmario_jump.png");
}
void GameObject::ApplyAnimation(SDL_Event &e){
    if (e.type == SDL_KEYDOWN){

        switch (e.key.keysym.sym) {
            case SDLK_RIGHT: {
                _frame = (_frame + 1) % 6;
                objectTexture = Tex[_frame];
                //srcRect = marioRect[_frame];
                //std::cout << _frame << std::endl;
                break;
            }
            case SDLK_LEFT: {
                _frame = (_frame + 1) % 6;
                objectTexture = fTex[_frame];
                break;
            }
        }
    }
    else if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_RIGHT: {
                objectTexture = DefaultTex;
                break;
            }
            case SDLK_LEFT: {
                objectTexture = fDefaultTex;
                break;
            }
        }
        _frame = 0;
    }
    //std::cout << "frame = " << _frame << std::endl;
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
    ypos += speedY * 2;
    if (space > 0) {
        ypos -= 32;
        space --;
    }
    int x1, x2, y1, y2;
    x1 = xpos / 32;
    x2 = (xpos + destRect.w - 1) / 32;

    y1 = ypos / 32;
    y2 = (ypos + destRect.h - 1) / 32;
    {
        if (Map::level_1[y2][x1] != 0 || Map::level_1[y2][x2] != 0) {
            ypos -= speedY * 2;
            onGround = true;
        }
        else onGround = false;
    {
        if (Map::level_1[y1][x1] !=0 || Map::level_1[y1][x2] != 0) {
            ypos += 32;
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




