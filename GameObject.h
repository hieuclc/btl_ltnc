#pragma once
#include "Game.h"
#include "Map.h"

class GameObject {
public:
    GameObject(const char* file, int x, int y);
    ~GameObject();
    void Update();
    void Render();
    void InputHandle(SDL_Event &e);
    void Move();
    SDL_Rect GetRect();
    static const int speedX = 4, speedY = 4;

    void LoadAnimation();
    int _frame = 0;
    float frame = 0;
    void ApplyAnimation();
    void Physics();
    bool CheckX();
    bool CheckY();
    bool Gravity();
    int surfaceX, surfaceY;
    int x_map, y_map;
    void CenterMapIndex();



private:
    int xpos, ypos, xvel, yvel;
    int up, left, right, space;
    int gravity = 10;

    bool onGround, jumped = false;
    SDL_Texture* objectTexture;
    SDL_Texture* fobjectTexture;

    SDL_Rect srcRect, destRect, mapRect;
    SDL_Rect marioRect[4];
};
