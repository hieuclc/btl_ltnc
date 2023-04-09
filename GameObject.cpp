#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
int temp = 0;
GameObject::GameObject(const char* file, int x, int y){
    objectTexture = TextureManager::LoadTexture(file);
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

}
void GameObject::Update(){
    destRect.h = srcRect.h;
    destRect.w = 24;
    destRect.x = xpos;
    destRect.y = ypos;
};

void GameObject::Render(){

    destRect.x = xpos - x_map;
    destRect.y = ypos - y_map;
    //SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
    if (right >=0) SDL_RenderCopy(Game::renderer, objectTexture, &marioRect[_frame], &destRect);
    if (left >=0) SDL_RenderCopy(Game::renderer, fobjectTexture, &marioRect[_frame], &destRect);
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
                if (onGround) space = 16; break;// yvel -= speedY * 8; break;
        }
    }
    else if (e.type == SDL_KEYUP){
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                yvel += speedY * 8; break;
            case SDLK_DOWN:
                yvel -= speedY; break;
            case SDLK_LEFT:
                xvel += speedX; left = 0; break;
            case SDLK_RIGHT:
                xvel -= speedX; right = 0; break;
            case SDLK_SPACE:
                //yvel += speedY * 8;
                break;
        }
    }


}


void GameObject::Move(){
    xpos += xvel;
    if (xpos < 0 || xpos + destRect.w > 7120 || CheckX()) xpos -= xvel;

    if (ypos < 0 || ypos + destRect.h > Game::SCREEN_HEIGHT || CheckY()) {
        ypos -= yvel;
    }
    std::cout << xpos << " " << ypos << std::endl;

}
SDL_Rect GameObject::GetRect(){
    return destRect;
}

void GameObject::LoadAnimation(){
    for (int i = 0; i < 5; i++) {
        marioRect[i].x = i * 24;
        marioRect[i].y = 0;
        marioRect[i].w = 24;
        marioRect[i].h = 32;
    }

    fobjectTexture = TextureManager::LoadTexture("assets/fmarioall.png");
}
void GameObject::ApplyAnimation(){
    if ((right == 1 || left == 1) && onGround) {
        if (frame >= 4.0) frame = 0;
        frame += 0.25;

        _frame = (int(frame) + 1) % 4;

    }
    else if (onGround) {_frame = 0; frame = 0;}
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
        space --;
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




