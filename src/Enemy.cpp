#include "Enemy.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <iostream>
const int speedX = 2, speedY = 2;
Enemy::Enemy(int x, int y, int _type){
    xpos = x;
    ypos = y;
    time = false;
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
    else if (_type == 3) {
        srcRect.x = srcRect.y = 0;
        srcRect.h = srcRect.w = 32;
        dead = false;
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.h = destRect.w = 32;
        type = 3;
    }
    else if (_type == 4) {
        srcRect.x = srcRect.y = 0;
        srcRect.h = srcRect.w = 32;
        dead = false;
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.h = destRect.w = 26;
        type = 4;
    }
    else if (_type == 5) {
        srcRect.x = srcRect.y = 0;
        srcRect.h = srcRect.w = 32;
        for (int j = 0; j < 2; j++) {
            plant[j].w = 32;
            plant[j].h = 44;
            plant[j].x = 32 * j;
            plant[j].y = 0;

        }
        dead = false;
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.h = 44;
        destRect.w = 32;
        i = 0;
        type = 5;
        plantY = 50;
    }
    plantLock = false;

}

Enemy::~Enemy(){};

void Enemy::Move(){
    if (type == 1) {
        i += 0.05;
    }
    else if (type == 5) {
        i += 0.1;
    }
    if (i >= 2) i = 0;
    _frame = int(i);
    pf = int(i);
    

    if (type == 1) {
        xpos += xvel;
        if (CheckX() || xpos < 0) {
            xpos -= xvel;
            xvel *= -1;
        }
        Enemy::Physics();
    }
}
void Enemy::Update(){
    destRect.w = destRect.h = 32;
    if (type == 5) destRect.h = 44;
    destRect.x = xpos - x_map;
    destRect.y = ypos;

    
 }
void Enemy::Render(){
    if (type == 1) {
        if (time)  _frame = 2;
        SDL_Texture* enemyTexture = TextureManager::LoadTexture("assets/images/goombas.png");
        SDL_RenderCopy(Game::renderer, enemyTexture, &goombas[_frame], &destRect);
        SDL_DestroyTexture(enemyTexture);
    }
    else if (type == 2) {
        SDL_Texture* enemyTexture = TextureManager::LoadTexture("assets/images/coin.png");
        SDL_RenderCopy(Game::renderer, enemyTexture, &srcRect, &destRect);
        SDL_DestroyTexture(enemyTexture);
    }
    else if (type == 3) {
        SDL_Texture* enemyTexture = TextureManager::LoadTexture("assets/images/end0_flag.png");
        SDL_RenderCopy(Game::renderer, enemyTexture, &srcRect, &destRect);
        SDL_DestroyTexture(enemyTexture);
    }
    else if (type == 4) {
        SDL_Texture* enemyTexture = TextureManager::LoadTexture("assets/images/heart.png");
        SDL_RenderCopy(Game::renderer, enemyTexture, &srcRect, &destRect);
        SDL_DestroyTexture(enemyTexture);
    }
    else if (type == 5) {
        SDL_Texture* enemyTexture = TextureManager::LoadTexture("assets/images/plant.png");
        SDL_RenderCopy(Game::renderer, enemyTexture, &plant[pf], &destRect);
        SDL_DestroyTexture(enemyTexture);
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
        if (Map::game_map[y1][x2] != 0 || Map::game_map[y2][x2] != 0) {
            return true;
        }
    }
    else if (xvel < 0) {
        if (Map::game_map[y1][x1] != 0 || Map::game_map[y2][x1] != 0) {
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
    if (Map::game_map[y2][x1] != 0 || Map::game_map[y2][x2] != 0) {
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

void Enemy::Flag(){
    if (ypos < 352) ypos += 2;
}

void Enemy::PlantMove(){
    if (plantY == 0 || plantY == -51) plantLock = true;

    if (!plantLock) {
        if (plantY > 0) {
            ypos += 1;
            plantY--;
        }
        else if (plantY < 0 && plantY >= -50) {
            ypos -= 1;
            plantY--;
        }
    }
    
    if (plantY == -52) {
        plantY = 50;
        plantLock = false;
    }
}
