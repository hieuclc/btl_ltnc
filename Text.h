#pragma once

#include "Game.h"
#include "TextureManager.h"
#include <string.h>
class Text {
public:
    Text(const char* _input, int& x, int& y, int& w, int& h, SDL_Color& _color, TTF_Font* _font);
    ~Text();
    void Render();
    void Free();
    SDL_Rect GetRect();
    SDL_Color color;
    TTF_Font* font = NULL;

private:
    int xpos, ypos;
    const char* input;


    SDL_Rect srcRect, destRect;


};
