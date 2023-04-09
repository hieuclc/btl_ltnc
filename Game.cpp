#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Enemy.h"
#include "Background.h"
#include <iostream>
GameObject* player;
Enemy* enemy;
Map* map;
SDL_Renderer* Game::renderer = nullptr;
int count = 0;
SDL_Rect srcR, destR;
Background* background;

Game::Game(){

}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 3, 173, 252, 255);
        isRunning = true;
    }
    else isRunning = false;
    player = new GameObject("assets/marioall.png",96, 384);
    map = new Map();
    enemy = new Enemy("assets/goombas.png",608,384);
    enemy->Goombas();
    background = new Background("assets11.bmp");
    background->LoadBackground();
    player->LoadAnimation();

};
void Game::handleEvents(){
    SDL_Event e;
    SDL_PollEvent (&e);
    //SDL_Delay(10);
    if (e.type == SDL_QUIT) isRunning = false;
    else {
        player->ApplyAnimation(e);
        player->InputHandle(e);
        //background->InputHandle(e);

    }

};
void Game::update(){
    player->Update();
    enemy->Update();
};
void Game::render(){
    SDL_RenderClear(renderer);
    background->Render();
player->Physics();
    enemy->Move();

    player->Move();
    player->CenterMapIndex();
    enemy->Render();
    player->Render();

    int a = 0;
    map->DrawMap();
    map->SetMap(player->x_map, a);
    enemy->SetMap(player->x_map);
    //map->DrawMap();

    SDL_RenderPresent(renderer);
};
void Game::inputHandle(SDL_Event e){
    player->InputHandle(e);
}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
};
bool running();
