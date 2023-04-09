#pragma once
#include "Game.h"
#include "GameObject.h"
class Background {
public:
    Background(const char* file);
    ~Background();
    void LoadBackground();
    void Render();
    void Scroll(SDL_Rect &rect);
    void InputHandle(SDL_Event &e);
    bool GetScrollingState();
private:
    int xsp;
    SDL_Rect bkgS, bkgD;
    SDL_Texture* background;
    bool isScrolling = true;
};
