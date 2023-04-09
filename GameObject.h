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
    void RestrictedMove();
    bool isLeft = true, isRight = true;
    void LoadAnimation();
    int _frame = 0;
    void ApplyAnimation(SDL_Event &e);
    void Physics();
    bool CheckX();
    bool CheckY();
    bool Gravity();
    void setCamera(SDL_Rect & Camera);
    int surfaceX, surfaceY;
    int x_map, y_map;
    void CenterMapIndex();



private:
    int xpos, ypos, xvel, yvel, space;
    int gravity = 10;

    bool onGround, jumped = false;
    SDL_Texture* objectTexture;
    SDL_Texture* enemyTexture;
    SDL_Texture* DefaultTex;
    SDL_Texture* fDefaultTex;
    SDL_Texture* JumpTex;
    SDL_Texture* fJumpTex;
    SDL_Texture* tTex;
    SDL_Texture* Tex[6];
    SDL_Texture* fTex[6];
    SDL_Rect srcRect, destRect, mapRect;
    SDL_Rect marioRect[4];
};
