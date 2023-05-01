#include "Text.h"
#include <SDL_ttf.h>
#include <iostream>
Text::Text(const char* input, int& x, int& y, int& w, int& h, int& tsize, SDL_Color &color, TTF_Font* font){
    TTF_Init();
    //TTF_Font* font = NULL; font = TTF_OpenFont("assets/font.ttf", tsize);
    SDL_Surface* surface = TTF_RenderText_Solid(font, input, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    xpos = x;
    ypos = y;
    srcRect.w = w;
    srcRect.h = h;
    srcRect.x = srcRect.y = 0;

    destRect.w = w;
    destRect.h = h;
    destRect.x = xpos;
    destRect.y = ypos;

    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
    SDL_FreeSurface(surface);
    surface = NULL;
    SDL_DestroyTexture(texture);
    texture = NULL;

}

Text::~Text(){};

SDL_Rect Text::GetRect(){
    return destRect;
}
