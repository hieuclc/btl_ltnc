#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
    void InputHandle(SDL_Event e);
    void Move();
    void RestrictedMove();
    static const int speedX = 5, speedY = 5;
    bool isLeft = false;
private:
    int xpos, ypos, xvel, yvel;
    SDL_Texture* playerTexure[3];
    SDL_Rect srcRect, destRect, frame[3];
};
