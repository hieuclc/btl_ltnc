#pragma once

#include "Game.h"
#include "TextureManager.h"
#include <string.h>
class Text {
public:
    Text(const char* input, int& x, int& y, int& w, int& h, int& tsize, SDL_Color& color, TTF_Font* font);
    ~Text();
    SDL_Rect GetRect();

private:
    int xpos, ypos;
    SDL_Rect srcRect, destRect;


};
