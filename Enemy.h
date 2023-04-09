#pragma once
#include "Game.h"
#include "GameObject.h"
class Enemy {
public:
    Enemy(const char* file, int x, int y);
    ~Enemy();
    void Move();
    void Update();
    void Render();
    SDL_Rect GetRect();
    bool CheckX();
    bool CheckY();
    void Physics();
    void SetMap(const int &x);
    int x_map;
    void Goombas();
    int GetX();
private:
    int xpos, ypos;
    float i = 0;
    int _frame = 0;
    int xvel = 0, yvel = 0;
    SDL_Rect srcRect, destRect;
    SDL_Rect goombas[11];
    SDL_Texture* enemyTexture;
};
