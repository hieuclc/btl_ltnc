#pragma once

#include "Game.h"
#include "TextureManager.h"
#include <string.h>
class Text {
public:
    Text(const char* input, int& x, int& y, SDL_Color& color);
    ~Text();
    void Render();
private:
    int xpos, ypos;
    SDL_Rect srcRect, destRect;


};
