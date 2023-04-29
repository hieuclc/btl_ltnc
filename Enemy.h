#pragma once
#include "Game.h"
#include "GameObject.h"
class Enemy {
public:
    Enemy(int x, int y, int _type);
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
    int GetX();
    int GetY();
    bool dead;
    int type = 0;
private:
    int xpos, ypos;
    float i = 0;
    int _frame = 0;
    int xvel = 0, yvel = 0;
    SDL_Rect srcRect, destRect;
    SDL_Rect goombas[3];


};
