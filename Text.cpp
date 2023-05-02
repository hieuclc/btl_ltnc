#include "Text.h"
#include <SDL_ttf.h>
#include <iostream>
Text::Text(const char* _input, int& x, int& y, int& w, int& h, SDL_Color &_color, TTF_Font* _font){

    xpos = x;
    ypos = y;
    srcRect.w = w;
    srcRect.h = h;
    srcRect.x = srcRect.y = 0;

    destRect.w = w;
    destRect.h = h;
    destRect.x = xpos;
    destRect.y = ypos;

    input = _input;

    font = _font;
    color = _color;




}

Text::~Text(){};

void Text::Render(){
    SDL_Surface* surface = TTF_RenderText_Solid(font, input, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
};

SDL_Rect Text::GetRect(){
    return destRect;
}

