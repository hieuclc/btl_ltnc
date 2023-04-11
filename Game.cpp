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
//Enemy* enemy = NULL;
//Enemy* enemy1 = NULL;
//Enemy* enemy2 = NULL;
//Enemy* enemy3 = NULL;
std::vector <Enemy*> ene;
Map* map;
//Text* text;
SDL_Renderer* Game::renderer = nullptr;
int count = 0;
SDL_Rect srcR, destR;
bool specialCreation = false;

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


    ene.push_back(new Enemy("assets/goombas.png",608,384));
    //ene.push_back(new Enemy("assets/goombas.png",608,384));
    ene.push_back(new Enemy("assets/goombas.png",300,384));
    //ene.push_back(new Enemy("assets/goombas.png",15,384));
    //ene.push_back(new Enemy("assets/goombas.png",15,384));
    ene.push_back(new Enemy("assets/goombas.png",1384,384));
    ene.push_back(new Enemy("assets/goombas.png",1672,384));
    ene.push_back(new Enemy("assets/goombas.png",1864,384));
    //ene.push_back(new Enemy("assets/goombas.png",5512,384));
    ene.push_back(new Enemy("assets/goombas.png",5376,384));
    ene.push_back(new Enemy("assets/goombas.png",5624,384));

    ene.push_back(new Enemy("assets/goombas.png",2500,160));



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

    if (player->GetX() >= 2016 && specialCreation == false) {

        specialCreation = true;
    }
    //if (player->life == 0)


};
void Game::render(){
    SDL_RenderClear(renderer);
    if (!player->won) {
    for (int i = 0; i < ene.size(); i++) {
        if (ene[i]->GetX() < player->x_map + 1000 && ene[i]->GetX() > player->x_map - 32) {
            ene[i]->Render();
            ene[i]->Move();
            ene[i]->SetMap(player->x_map);
            SDL_Rect r = ene[i]->GetRect();
            SDL_Rect pr = player->GetRect();
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

    //text->TextLoad("halo", x, y, color);
    delete text;
    SDL_RenderPresent(renderer);
    if (player->playing == false) {
        //SDL_Delay(1000);
        //isRunning = false;
        //life--;
    }
//    if (player->GetX() >= )
    }
    else {
        player->win();
    }
};

void Game::clean(){
    delete player;
    delete map;
//    delete enemy;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

};
bool running();
