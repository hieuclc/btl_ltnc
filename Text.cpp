#include "Text.h"
//#include <SDL_ttf.h>
#include <iostream>
Text::Text(const char* input, int& x, int& y, SDL_Color &color){
    TTF_Init();
    TTF_Font* font = NULL; font = TTF_OpenFont("assets/font.ttf", 20);
    SDL_Surface* surface = TTF_RenderText_Solid(font, input, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    xpos = x;
    ypos = y;
    srcRect.w = 128;
    srcRect.h = 32;
    srcRect.x = srcRect.y = 0;

    destRect.w = 128;
    destRect.h = 32;
    destRect.x = xpos;
    destRect.y = ypos;

    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
    SDL_FreeSurface(surface);
    surface = NULL;
    SDL_DestroyTexture(texture);
    texture = NULL;
}

Text::~Text(){};
