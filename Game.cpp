#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Enemy.h"
#include "Background.h"
#include "Text.h"
#include <iostream>
#include <vector>
GameObject* player = NULL;
std::vector <Enemy*> ene;
Map* map;
SDL_Renderer* Game::renderer = NULL;
int count = 0;
SDL_Rect srcR, destR;
//bool specialCreation = false;

Game::Game(){
    life = 3;
}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0) {

        window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 3, 173, 252, 255);
        isRunning = true;
    }
    else isRunning = false;
    player = new GameObject("assets/marioall.png",96, 384);
    map = new Map();

    player->LoadAnimation();


    ene.push_back(new Enemy(608,384,1));
    ene.push_back(new Enemy(300,384,1));
    ene.push_back(new Enemy(1384,384,1));
    ene.push_back(new Enemy(1672,384,1));
    ene.push_back(new Enemy(1864,384,1));
    ene.push_back(new Enemy(2500,160,1));
    ene.push_back(new Enemy(5344,384,1));
    ene.push_back(new Enemy(5624,384,1));



    ene.push_back(new Enemy(576,160,2));
    ene.push_back(new Enemy(2592,160,2));
    ene.push_back(new Enemy(2752,160,2));
    ene.push_back(new Enemy(2880,384,2));
    ene.push_back(new Enemy(3168,256,2));
    ene.push_back(new Enemy(3392,256,2));
    ene.push_back(new Enemy(3456,256,2));
    ene.push_back(new Enemy(3520,256,2));
    ene.push_back(new Enemy(3456,160,2));

    ene.push_back(new Enemy(2884,384,2));
    ene.push_back(new Enemy(2976,256,2));
    ene.push_back(new Enemy(3808,160,2));
    ene.push_back(new Enemy(4064,256,2));
    ene.push_back(new Enemy(4864,256,2));
    ene.push_back(new Enemy(5440,256,2));


};
void Game::handleEvents(){
    SDL_Event e;
    SDL_PollEvent (&e);
    SDL_Delay(10);
    if (e.type == SDL_QUIT) isRunning = false;
    else {
        player->InputHandle(e);

    }

};
void Game::update(){
    player->Update();
    for (int i = 0; i < ene.size(); i++) {ene[i]->Update();}



};
void Game::render(){
    SDL_RenderClear(renderer);
    if (!player->won) {
    int _size = ene.size();
    for (int i = 0; i < _size; i++) {
        if (ene[i]->GetX() < player->x_map + 1000 && ene[i]->GetX() > player->x_map - 32) {
            if (ene[i]->GetY() >= SCREEN_HEIGHT) delete ene[i];
            if (ene[i]->type == 1) {
                ene[i]->Move();
            }
            ene[i]->Render();
            ene[i]->SetMap(player->x_map);
            SDL_Rect r = ene[i]->GetRect();
            SDL_Rect pr = player->GetRect();
            if (player->GetY() >= SCREEN_HEIGHT - 32) player->dead = true;
            if (ene[i] ->type == 1) {
                if(player->DeadCheck(r) && player->Jumped(r) && player->dead == false) {
                    delete ene[i];
                    //ene[i] = NULL;
                    ene.erase(ene.begin() + i);
                    player->Bounce();
                    score++;

                }
            else if (TextureManager::PlayerCollisionChecker(pr, r) && !player->Jumped(r)) {
                    player->dead = true;
                    //ene.erase(ene.begin() + i);
                }
            }
            else if (ene[i]->type == 2) {
                if (player->DeadCheck(r)){
                    delete ene[i];
                    ene.erase(ene.begin() + i);
                    score++;
                }
            }
        }

    }
        int x = 10, y = 10;SDL_Color color = {0,0,0};
        std::string temp = "Score: " + std::to_string(score);
        std::cout << temp << std::endl;
        const char* _score = temp.c_str();

        Text* text = new Text(_score, x, y, color);
        //delete[] _score;
        player->Physics();
        player->ApplyAnimation();
        player->Move();
        player->CenterMapIndex();
        player->Render();
        map->DrawMap();
        map->SetMap(player->x_map);

        delete text;
        SDL_RenderPresent(renderer);
    }
    else {
        int x = 10, y = 10;SDL_Color color = {0,0,0};
        Text* text = new Text ("you won", x, y, color);
        delete text;
        SDL_RenderPresent(renderer);
    }
};

void Game::clean(){
    delete player;
    delete map;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

};
bool running();
