#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Enemy.h"
#include "Background.h"
#include "Text.h"
#include "Menu.h"
#include <iostream>
#include <vector>
GameObject* player = NULL;
std::vector <Enemy> ene;
Enemy enemi = Enemy(608, 384, 1);
Map* map;
SDL_Renderer* Game::renderer = NULL;
TTF_Font* font = NULL;
int count = 0;
SDL_Rect srcR, destR;

Game::Game(){
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
    player = new GameObject("assets/marioall.png", 96, 384);
    map = new Map();
    font =  TTF_OpenFont("assets/font.ttf", 20);
    player->LoadAnimation();
    canPlay = false;
    _quit = false;
};

void Game::load(){
    ene.erase(ene.begin(), ene.end());

    ene.push_back(Enemy(608,384,1));
    ene.push_back(Enemy(300,384,1));
    ene.push_back(Enemy(1384,384,1));
    ene.push_back(Enemy(1672,384,1));
    ene.push_back(Enemy(1864,384,1));
    ene.push_back(Enemy(2500,160,1));
    ene.push_back(Enemy(5344,384,1));
    ene.push_back(Enemy(5624,384,1));



    ene.push_back(Enemy(576,160,2));
    ene.push_back(Enemy(2592,160,2));
    ene.push_back(Enemy(2752,160,2));
    ene.push_back(Enemy(2880,384,2));
    ene.push_back(Enemy(3168,256,2));
    ene.push_back(Enemy(3392,256,2));
    ene.push_back(Enemy(3456,256,2));
    ene.push_back(Enemy(3520,256,2));
    ene.push_back(Enemy(3456,160,2));

    ene.push_back(Enemy(2884,384,2));
    ene.push_back(Enemy(2976,256,2));
    ene.push_back(Enemy(3808,160,2));
    ene.push_back(Enemy(4064,256,2));
    ene.push_back(Enemy(4864,256,2));
    ene.push_back(Enemy(5440,256,2));
}

void Game::menu(){
    SDL_RenderClear(renderer);
    SDL_Texture* temp = TextureManager::LoadTexture("assets/menu.png");
    SDL_Rect tempR = {64, 64, 352, 210};
    SDL_RenderCopy(renderer, temp, NULL, &tempR);
    SDL_DestroyTexture(temp);
    int x = 224, y = 288, w = 64, h = 32, tsize = 20;
    SDL_Color color = {255,255,255};
    Text play = Text("Play",x, y, w, h, tsize, color, font);
    y += 64;
    w = 145;
    Text quit = Text("Quit game",x , y, w, h, tsize, color, font);
    SDL_Event e;
    SDL_PollEvent (&e);
    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            {
                SDL_Rect playRect = play.GetRect();
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);
                SDL_Rect mrect;
                mrect.x = xm;
                mrect.y = ym;
                if (TextureManager::PlayerCollisionChecker(playRect, mrect)) {
                    canPlay = true;
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    break;
                }
                playRect = quit.GetRect();
                if (TextureManager::PlayerCollisionChecker(playRect, mrect)) {
                    canPlay = true;
                    isRunning = false;
                    _quit = true;
                    break;
                }
            }
    }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

}
void Game::start(){
    isRunning = true;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int x = 336, y = 208, w = 128, h = 32, tsize = 20;
    SDL_Color color = {255,255,255};
    Text play = Text("Loading...", x, y, w, h, tsize, color, font);
    std::string temp = "Life: " + std::to_string(life);
    const char* lif = temp.c_str();
    y += 64;
    Text life = Text(lif, x, y, w, h, tsize, color, font);


    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_SetRenderDrawColor(renderer, 3, 173, 252, 255);

}
void Game::handleEvents(){
    SDL_Event e;
    SDL_PollEvent (&e);
    if (e.type == SDL_QUIT) {
        isRunning = false;
        _quit = true;
    }
    else {
        player->InputHandle(e);

    }

};
void Game::update(){
    player->Update();
    for (int i = 0; i < ene.size(); i++) {ene[i].Update();}
};
void Game::render(){
    //std::cout << &enemi << std::endl;
    SDL_RenderClear(renderer);
    if (!player->won) {
    int _size = ene.size();
    if (player->GetY() >= SCREEN_HEIGHT - 32) player->dead = true;
    for (int i = 0; i < _size; i++) {
        if (ene[i].GetX() < player->x_map + 1000 && ene[i].GetX() > player->x_map - 32) {
            if (ene[i].GetY() >= SCREEN_HEIGHT) ene[i].dead = true;
            if (ene[i].type == 1) {
                ene[i].Move();
            }
            if(!ene[i].dead) ene[i].Render();
            ene[i].SetMap(player->x_map);
            SDL_Rect r = ene[i].GetRect();
            SDL_Rect pr = player->GetRect();

            if (ene[i].type == 1) {
                if(player->DeadCheck(r) && player->Jumped(r) && player->dead == false && ene[i].dead == false) {
                    ene[i].dead = true;
                    player->Bounce();
                    score++;

                }
            else if (TextureManager::PlayerCollisionChecker(pr, r) && !player->Jumped(r) && ene[i].dead == false) {
                    player->dead = true;
                }
            }
            else if (ene[i].type == 2 && ene[i].dead == false) {
                if (player->DeadCheck(r)){
                    ene[i].dead = true;
                    score++;
                }
            }
        }

    }
        int x = 10, y = 10, w = 128, h = 32, tsize = 20;
        SDL_Color color = {0,0,0};
        std::string temp = "Score: " + std::to_string(score);

        const char* _score = temp.c_str();

        Text text = Text(_score, x, y, w, h, tsize, color, font);
        player->Physics();
        player->ApplyAnimation();
        player->Move();
        player->CenterMapIndex();
        player->Render();
        map->DrawMap();
        map->SetMap(player->x_map);

        SDL_RenderPresent(renderer);
        std::cout << player << std::endl;
    }
    else {
        int x = 10, y = 10, w = 128, h = 32, tsize = 20;
        SDL_Color color = {0,0,0};
        Text text = Text ("you won", x, y, w, h, tsize, color, font);

        SDL_RenderPresent(renderer);
    }
};
void Game::die(){
    if (player->playing == false) {
        isRunning = false;
        player->playing = true;
        life--;
        player->SetPos();
    }
}

void Game::clean(){

    TTF_CloseFont(font);
    font = NULL;
    free(map);
    free(player);
    map = NULL;
    player = NULL;
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    for (int i = 0; i < ene.size(); i++) ene.erase(ene.begin() + i);

};

void Game::end(){
    SDL_RenderClear(renderer);
    int x = 224, y = 288, w = 64, h = 32, tsize = 20;
    SDL_Color color = {255,255,255};
    Text play = Text("Over!!!!!",x, y, w, h, tsize, color, font);
    SDL_RenderPresent(renderer);
}

