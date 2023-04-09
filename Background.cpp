#include "Background.h"
#include "TextureManager.h"
Background::Background(const char* file){
    background = TextureManager::LoadTexture(file);
    xsp = 0;
};

Background::~Background(){};

void Background::LoadBackground(){
    bkgS.x = bkgS.y = 0;
    bkgS.h = 480;
    bkgS.w = 7168;
    bkgD.x = bkgD.y = 0;
    bkgD.h = 480;
    bkgD.w = 7168;
}

void Background::Render(){
    SDL_RenderCopy(Game::renderer, background, &bkgS, &bkgD);
}
void Background::Scroll(SDL_Rect &rect){
        if (isScrolling){
            bkgD.x -= xsp;
            if (bkgD.x > 0) bkgD.x += xsp;
        };
        //if (bkgD.x <= -(7120 - Game::SCREEN_WIDTH)) isScrolling = false;
}
void Background::InputHandle(SDL_Event &e){
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                xsp -= GameObject::speedX; break;
            case SDLK_RIGHT:
                xsp += GameObject::speedX; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                xsp += GameObject::speedX; break;
            case SDLK_RIGHT:
                xsp -= GameObject::speedX; break;
        }
    }
};
bool Background::GetScrollingState(){
    return isScrolling;
};
