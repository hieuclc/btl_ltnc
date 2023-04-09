#include "Player.h"
#include "TextureManager.h"
#include <iostream>

void Player::InputHandle(SDL_Event e){
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            yvel -= speedY; std::cout << "UP\n"; break;
        case SDLK_DOWN:
            yvel += speedY; std::cout << "DOWN\n"; break;
        case SDLK_LEFT:
            xvel -= speedX; isLeft = true; std::cout << "LEFT\n"; break;
        case SDLK_RIGHT:
            xvel += speedX; std::cout << "RIGHT\n"; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0){
        isLeft = false;
        switch (e.key.keysym.sym) {
        case SDLK_UP:
            yvel += speedY; std::cout << "UP\n"; break;
        case SDLK_DOWN:
            yvel -= speedY; std::cout << "DOWN\n"; break;
        case SDLK_LEFT:
            xvel += speedX; std::cout << "LEFT\n"; break;
        case SDLK_RIGHT:
            xvel -= speedX; std::cout << "RIGHT\n"; break;
        }
    }
}
void Player::Move(){
    xpos += xvel;
    if (xpos < 0 || xpos + destRect.w > Game::SCREEN_WIDTH ) xpos -= xvel;
    ypos += yvel;
    if (ypos < 0 || ypos + destRect.h > Game::SCREEN_HEIGHT) ypos -= yvel;

}
void Player::RestrictedMove(){
    ypos += yvel;
    if (ypos < 0 || ypos + destRect.h > Game::SCREEN_HEIGHT) ypos -= yvel;
}
