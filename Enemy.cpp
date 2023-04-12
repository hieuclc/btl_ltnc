#include "Enemy.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <iostream>
const int speedX = 2, speedY = 2;
Enemy::Enemy(int x, int y, int _type){
    xpos = x;
    ypos = y;
    if (_type == 1) {
        srcRect.x = srcRect.y = 0;
        srcRect.h = 32;
        srcRect.w = 96;
        xvel += speedX;
        yvel += speedY;
        dead = false;
        for (int j = 0; j < 3; j++) {
            goombas[j].x = 32 * j;
            goombas[j].y = 0;
            goombas[j].h = goombas[j].w = 32;
        }

        i = 0;
        type = 1;
    }
    else if (_type == 2) {
        srcRect.x = srcRect.y = 0;
        srcRect.h = srcRect.w = 32;
        dead = false;
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.h = destRect.w = 32;
        type = 2;
    }

}

Enemy::~Enemy(){};

void Enemy::Move(){
    xpos += xvel;
    i += 0.05;
    if (i >= 2) i = 0;
    _frame = int(i);

    if (CheckX() || xpos < 0) {
        xpos -= xvel;
        xvel *= -1;
    }
    Enemy::Physics();

}
void Enemy::Update(){
    destRect.w = destRect.h = 32;
    destRect.x = xpos - x_map;
    destRect.y = ypos;
 }
void Enemy::Render(){
    if (type == 1) {
        SDL_Texture* enemyTexture = TextureManager::LoadTexture("assets/goombas.png");
        SDL_RenderCopy(Game::renderer, enemyTexture, &goombas[_frame], &destRect);
        SDL_DestroyTexture(enemyTexture);
        enemyTexture = NULL;
    }
    else if (type == 2) {
        SDL_Texture* enemyTexture = TextureManager::LoadTexture("assets/coin.png");
        SDL_RenderCopy(Game::renderer, enemyTexture, &srcRect, &destRect);
        SDL_DestroyTexture(enemyTexture);
        enemyTexture = NULL;
    }

}
SDL_Rect Enemy::GetRect(){
    return destRect;
}

bool Enemy::CheckX(){
    int x1, x2, y1, y2;
    x1 = xpos / 32;
    x2 = (xpos + destRect.w - 1) / 32;

    y1 = ypos / 32;
    y2 = (ypos + destRect.h - 1) / 32;

    if (xvel > 0) {
        if (Map::level_1[y1][x2] != 0 || Map::level_1[y2][x2] != 0) {
            return true;
        }
    }
    else if (xvel < 0) {
        if (Map::level_1[y1][x1] != 0 || Map::level_1[y2][x1] != 0) {
            return true;
        }
    }

    return false;
}
void Enemy::Physics(){
    ypos += speedY;
    int x1, x2, y2;
    x1 = xpos / 32;
    x2 = (xpos + destRect.w - 1) / 32;

    y2 = (ypos + destRect.h - 1) / 32;
    if (Map::level_1[y2][x1] != 0 || Map::level_1[y2][x2] != 0) {
        ypos -= speedY;
    }
}

void Enemy::SetMap(const int& x){
    x_map = x;
}

int Enemy::GetX(){
    return xpos;
}

int Enemy::GetY(){
    return ypos;
}

