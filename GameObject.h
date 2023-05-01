#pragma once
#include "Game.h"
#include "Map.h"
class GameObject {
public:
    GameObject();
    void create(int x, int y);
    GameObject(const char* file, int x, int y);
    ~GameObject();
    void Update();
    void Render();
    void InputHandle(SDL_Event &e);
    void Move();
    SDL_Rect GetRect();
    static const int speedX = 4, speedY = 4;

    int _frame = 0;
    float frame = 0;
    void ApplyAnimation();
    void Physics();
    bool CheckX();
    bool CheckY();
    int surfaceX, surfaceY;
    int x_map, y_map;
    void CenterMapIndex();
    bool dead;
    int dead_ani;
    int life;
    bool check = false;
    bool playing;
    bool DeadCheck(SDL_Rect &enemyRect);
    int GetX();
    int GetY();
    bool Jumped(SDL_Rect &enemyRect);
    void Bounce();
    bool won;
    void win();
    void SetPos();

    bool onGround;
    int space;
private:
    int xpos, ypos, xvel, yvel;
    int left, right;
    int bounce;
    int gravity = 10;
    SDL_RendererFlip flip;


    SDL_Rect srcRect, destRect, mapRect;
    SDL_Rect marioRect[6];
};
