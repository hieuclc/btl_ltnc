#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Enemy.h"
class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* file);
    static void Draw(SDL_Texture* tex, SDL_Rect& src, SDL_Rect& dest);
    static bool PlayerCollisionChecker (SDL_Rect &playerR, SDL_Rect &enemyR);
};
