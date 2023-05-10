#include "TextureManager.h"
SDL_Texture* TextureManager::LoadTexture(const char* file){
    SDL_Texture* tex = IMG_LoadTexture(Game::renderer, file);
    return tex;

}


void TextureManager::Draw(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
};

bool TextureManager::PlayerCollisionChecker(SDL_Rect &playerR, SDL_Rect &enemyR){
    int p_left = playerR.x;
    int p_right = playerR.x + playerR.w;
    int p_top = playerR.y;
    int p_bot = playerR.y + playerR.h;

    int e_left = enemyR.x;
    int e_right = enemyR.x + enemyR.w;
    int e_top = enemyR.y;
    int e_bot = enemyR.y + enemyR.h;

    if (p_bot <= e_top) return false;
    if (p_top >= e_bot) return false;
    if (p_right <= e_left) return false;
    if (p_left >= e_right) return false;
    return true;

};

bool TextureManager::MouseCheck(int &x, int &y, SDL_Rect &rect){
    int left = rect.x;
    int right = rect.x + rect.w;
    int top = rect.y;
    int bot = rect.y + rect.h;
    if (left <= x && x <= right) if (top <= y && y <= bot) return true;
    return false;
};
