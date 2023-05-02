#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Enemy.h"
#include "Text.h"
#include <iostream>
#include <vector>
#include <SDL_mixer.h>

int count = 0;
int Die;
Uint32 startTicks = 0;

GameObject* player = NULL;
std::vector <Enemy> ene;
std::vector <Enemy> heart;
std::vector <Uint32> eneTime;

Map* map;
SDL_Renderer* Game::renderer = NULL;
SDL_Surface* surface = NULL;
SDL_Texture* background = NULL;
TTF_Font* font = NULL;
TTF_Font* sfont = NULL;



SDL_Rect srcR, destR;

Mix_Music* mainMusic = NULL;
Mix_Music* deadMusic = NULL;
Mix_Music* endMusic = NULL;
Mix_Music* closeMusic = NULL;
Mix_Chunk* jump = NULL;
Mix_Chunk* mob = NULL;
Mix_Chunk* coin = NULL;


Text* play = NULL;
Text* quit = NULL;

Game::Game(){
}
Game::~Game(){

}
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0 && TTF_Init() == 0 && Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) >= 0) {

        window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 3, 173, 252, 255);
        isRunning = true;
    }
    else isRunning = false;

    background = TextureManager::LoadTexture("assets/images/background.png");
    surface = IMG_Load("assets/images/icon.png");
    SDL_SetWindowIcon(window, surface);
    player = new GameObject("assets/marioall.png", 96, 384);
    map = new Map();
    font =  TTF_OpenFont("assets/font.ttf", 20);
    sfont =  TTF_OpenFont("assets/font.ttf", 15);

    canPlay = false;
    _quit = false;

    heart.push_back(Enemy(680, 10, 4));
    heart.push_back(Enemy(712, 10, 4));
    heart.push_back(Enemy(744, 10, 4));

    mainMusic = Mix_LoadMUS("assets/sounds/bkg_music.wav");
    deadMusic = Mix_LoadMUS("assets/sounds/death.wav");
    endMusic = Mix_LoadMUS("assets/sounds/levelend.wav");
    closeMusic = Mix_LoadMUS("assets/sounds/end.wav");
    jump = Mix_LoadWAV("assets/sounds/jump.wav");
    mob = Mix_LoadWAV("assets/sounds/mob.wav");
    coin = Mix_LoadWAV("assets/sounds/coin.wav");

    victory = false;
    endMus = false;
    close = false;

    int x = 224, y = 288, w = 64, h = 32;
    SDL_Color color = {255,255,255};
    play = new Text("Play",x, y, w, h, color, font);
    y += 64;
    w = 145;
    quit = new Text("Quit game",x , y, w, h, color, font);

};

void Game::load(){
    ene.erase(ene.begin(), ene.end());
    eneTime.erase(eneTime.begin(), eneTime.end());

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

    ene.push_back(Enemy(6223, 126, 3));

    for (int i = 0; i < ene.size(); i++) eneTime.push_back(0);

    Mix_PlayMusic(mainMusic, -1);
    Die = 0;
    startTicks = 0;
    score = 0;
    player->dead = false;
    isRunning = true;
}

void Game::menu(){
    SDL_RenderClear(renderer);
    SDL_Texture* temp = TextureManager::LoadTexture("assets/images/menu.png");
    SDL_Rect tempR = {64, 64, 352, 210};
    SDL_RenderCopy(renderer, temp, NULL, &tempR);
    SDL_DestroyTexture(temp);

    play->Render();
    quit->Render();

    SDL_Event e;
    SDL_PollEvent (&e);
            {
                SDL_Rect playRect = play->GetRect();
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);


                if (TextureManager::MouseCheck(xm, ym, playRect)) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        canPlay = true;
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    }
                    play->color = {255,255,0};
                }
                else play->color = {255,255,255};
                SDL_Rect quitRect = quit->GetRect();
                if (TextureManager::MouseCheck(xm, ym, quitRect)) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        canPlay = true;
                        isRunning = false;
                        _quit = true;
                    }
                    quit->color = {255,255,0};
                }
                else quit->color = {255,255,255};
            }

    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);

}
void Game::start(){
    isRunning = true;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int x = 336, y = 208, w = 128, h = 32;
    SDL_Color color = {255,255,255};
    Text _loading = Text("Loading...", x, y, w, h, color, font);
    _loading.Render();
    std::string temp = "Life: " + std::to_string(life);
    const char* lif = temp.c_str();
    y += 64;
    Text life = Text(lif, x, y, w, h, color, font);
    life.Render();


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
        if (player->space == 16) {
            Mix_PlayChannel(-1, jump, 0);
        }
    }

};
void Game::update(){
    if (Die < 2) Die = player->dead;
    player->Update();
    for (int i = 0; i < ene.size(); i++) {ene[i].Update();}
    if (Die == 1) {
        if (Mix_PlayingMusic()) Mix_HaltMusic();
        Mix_PlayMusic(deadMusic, 0);
        Die = 2;
    }
};
void Game::render(){
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, NULL, NULL);

    int x = 10, y = 10, w = 128, h = 32;
    SDL_Color color = {0,0,0};
    std::string temp = "Score: " + std::to_string(score);

    const char* _score = temp.c_str();

    Text text = Text(_score, x, y, w, h, color, font);
    text.Render();

    for (int i = 0; i < life; i++) heart[i].Render();

    if (!player->won) {
    int _size = ene.size();
    if (player->GetY() >= SCREEN_HEIGHT - 32) player->dead = true;
    for (int i = 0; i < _size; i++) {
        if (ene[i].GetX() < player->x_map + 1000 && ene[i].GetX() > player->x_map - 32) {
            if (ene[i].GetY() >= SCREEN_HEIGHT) ene[i].dead = true;
            if (ene[i].type == 1 && !ene[i].time) {
                ene[i].Move();
            }
            if(!ene[i].dead) ene[i].Render();
            ene[i].SetMap(player->x_map);
            SDL_Rect r = ene[i].GetRect();
            SDL_Rect pr = player->GetRect();

            if (ene[i].type == 1) {

                if (SDL_GetTicks() - eneTime[i] >= 500 && ene[i].time) ene[i].dead = true; ;
                if (player->DeadCheck(r) && player->Jumped(r) && player->dead == false && ene[i].dead == false) {
                    if (!ene[i].time) {
                        player->Bounce();
                        eneTime[i] = SDL_GetTicks();
                        ene[i].time = true;
                        score++;
                        Mix_PlayChannel(-1, mob, 0);

                    }
                    //ene[i]._frame = 2;





                }
            else if (TextureManager::PlayerCollisionChecker(pr, r) && !player->Jumped(r) && ene[i].dead == false && !ene[i].time) {
                    player->dead = true;
                }
            }
            else if (ene[i].type == 2 && ene[i].dead == false) {
                if (player->DeadCheck(r)){
                    ene[i].dead = true;
                    score++;
                    Mix_PlayChannel(-1, coin, 0);
                }
            }
        }

    }

        if (player->GetY() <= 448) player->Physics();
        player->ApplyAnimation();
        player->Move();
        player->CenterMapIndex();

        map->DrawMap();
        map->SetMap(player->x_map);

        SDL_RenderPresent(renderer);
    }
    else {


        if (!endMus){Mix_HaltMusic(); Mix_PlayMusic(endMusic, 0); endMus = true;}

        ene.back().Render();
        ene.back().SetMap(player->x_map);
        ene.back().Flag();

        map->DrawMap();
        map->SetMap(player->x_map);
        player->ApplyAnimation();
        player->CenterMapIndex();
        if (!player->endtime) {
            player->win();
            startTicks = SDL_GetTicks();
        }
        else if (SDL_GetTicks() - startTicks >= 1000) {
            victory = true;
            startTicks = SDL_GetTicks();
            SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        }
        SDL_RenderPresent(renderer);
    }
};
void Game::die(){
    if (Die == 2) {
        startTicks = SDL_GetTicks();
        Die = 3;
    }
    if (Die == 3) {
        if (SDL_GetTicks() - startTicks >= 4000) {
            Die = -1;
            if (player->playing == false) {
                if (true) {
                    isRunning = false;
                    player->playing = true;
                    life--;
                    player->SetPos();
                }
            }
        }
    }


}

void Game::clean(){

    TTF_CloseFont(font);
    TTF_CloseFont(sfont);
    sfont = NULL;
    font = NULL;

    free(map);
    free(player);
    map = NULL;
    player = NULL;


    free(play);
    free(quit);

    Mix_FreeMusic(mainMusic);
    Mix_FreeMusic(deadMusic);
    Mix_FreeMusic(endMusic);
    Mix_FreeMusic(closeMusic);
    Mix_FreeChunk(jump);
    Mix_FreeChunk(mob);
    Mix_FreeChunk(coin);

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    for (int i = 0; i < ene.size(); i++) ene.erase(ene.begin() + i);
    for (int i = 0; i < eneTime.size(); i++) eneTime.erase(eneTime.begin() + i);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();

};

void Game::end(){
    SDL_RenderClear(renderer);
    if (!close) Mix_PlayMusic(closeMusic, 0);
    if (victory) {
        while (SDL_GetTicks() - startTicks <= 10000) {
            int x = 200, y = 240, w = 128, h = 36;
            SDL_Color color = {255,255,255};
            Text the_end = Text("You won!",x ,y, w, h, color, font);
            the_end.Render();
            std::string temp = "Score: " + std::to_string(score);
            const char* _score = temp.c_str();
            y += 40;
            Text score = Text(_score, x, y, w, h, color, font);
            score.Render();
            SDL_RenderPresent(renderer);
        }
    }
    else {
        while (SDL_GetTicks() - startTicks <= 10000) {
            int x = 200, y = 240, w = 128, h = 32;
            SDL_Color color = {255,255,255};
            Text the_end = Text("You lose!",x , y, w, h, color, font);
            the_end.Render();
            SDL_RenderPresent(renderer);
        }
    }

}
