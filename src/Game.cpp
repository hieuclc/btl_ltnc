#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Enemy.h"
#include "Text.h"
#include "Timer.h"
#include <vector>

#include <iostream>
#include <SDL_mixer.h>

int count = 0;
int Die;
Uint32 startTicks = 0;
bool Game::paused = false;

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
Timer* time;



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
Text* help = NULL;

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
    player = new GameObject(96, 384);
    
    map = new Map();
    map_no = 2;
    font =  TTF_OpenFont("assets/font.ttf", 20);
    sfont =  TTF_OpenFont("assets/font.ttf", 18);
    time = new Timer;

    canPlay = false;
    _quit = false;
    instructions = false;

    heart.push_back(Enemy(680, 10, 4));
    heart.push_back(Enemy(712, 10, 4));
    heart.push_back(Enemy(744, 10, 4));

    

    victory = false;
    endMus = false;
    close = false;
    paused = false;

    int x = 224, y = 288, w = 64, h = 32;
    SDL_Color color = {255,255,255};
    play = new Text("Play", x, y, w, h, color, font);
    y += 64;
    w = 160;
    help = new Text("Instructions", x, y, w, h, color, font);
    y += 64;
    w = 145;
    quit = new Text("Quit game", x, y, w, h, color, font);

    
    life = 3;
    int temp = 0;
    highScore(temp);

};

void Game::load(){
    close = false;
    endGame = false;

    ene.erase(ene.begin(), ene.end());
    eneTime.erase(eneTime.begin(), eneTime.end());

    Mix_FreeMusic(mainMusic);
    Mix_FreeMusic(deadMusic);
    Mix_FreeMusic(endMusic);
    Mix_FreeMusic(closeMusic);
    Mix_FreeChunk(jump);
    Mix_FreeChunk(mob);
    Mix_FreeChunk(coin);

    if (map_no == 1) {
        map->LoadMap(Map::level_1);
        mainMusic = Mix_LoadMUS("assets/sounds/bkg_music.wav");
        endMusic = Mix_LoadMUS("assets/sounds/levelend.wav");

        ene.push_back(Enemy(608,384,1));
        ene.push_back(Enemy(300,384,1));
        ene.push_back(Enemy(1384,384,1));
        ene.push_back(Enemy(1672,384,1));
        ene.push_back(Enemy(1890,384,1));
        ene.push_back(Enemy(2500,160,1));
        ene.push_back(Enemy(5344,384,1));
        ene.push_back(Enemy(5624,384,1));

        ene.push_back(Enemy(448,288,2));
        ene.push_back(Enemy(480,288,2));
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
        
        ene.push_back(Enemy(1040,288,5));
        ene.push_back(Enemy(1424,256,5));
        ene.push_back(Enemy(5744,320,5));

        ene.push_back(Enemy(6223, 126, 3));

        for (int i = 0; i < ene.size(); i++) eneTime.push_back(0);

    }
    else if (map_no == 2) {
        map->LoadMap(Map::level_2);
        mainMusic = Mix_LoadMUS("assets/sounds/blk_music.wav");
        endMusic = Mix_LoadMUS("assets/sounds/levelend_2.wav");

        ene.push_back(Enemy(712,384,1));
        ene.push_back(Enemy(650,384,1));
        ene.push_back(Enemy(500,384,1));
        ene.push_back(Enemy(960,384,1));
        ene.push_back(Enemy(2632,384,1));
        ene.push_back(Enemy(3488,384,1));
        ene.push_back(Enemy(3616,384,1));
        ene.push_back(Enemy(5384,384,1));
        ene.push_back(Enemy(5532,384,1));

        ene.push_back(Enemy(1344,224,2));
        ene.push_back(Enemy(1408,224,2));
        ene.push_back(Enemy(1504,224,2));
        ene.push_back(Enemy(1888,64,2));
        ene.push_back(Enemy(2304,224,2));
        ene.push_back(Enemy(5120,224,2));
        ene.push_back(Enemy(4416,384,2));
        ene.push_back(Enemy(4456,192,2));
        ene.push_back(Enemy(4480,224,2));
        ene.push_back(Enemy(4448,224,2));

        ene.push_back(Enemy(2544,256,5));
        ene.push_back(Enemy(3440,256,5));
        ene.push_back(Enemy(3568,288,5));
        ene.push_back(Enemy(3696,256,5));
        ene.push_back(Enemy(5424,256,5));
        ene.push_back(Enemy(5744,320,5));

        ene.push_back(Enemy(6223, 126, 3));

        for (int i = 0; i < ene.size(); i++) eneTime.push_back(0);
        
    }

    deadMusic = Mix_LoadMUS("assets/sounds/death.wav");
    closeMusic = Mix_LoadMUS("assets/sounds/end.wav");
    jump = Mix_LoadWAV("assets/sounds/jump.wav");
    mob = Mix_LoadWAV("assets/sounds/mob.wav");
    coin = Mix_LoadWAV("assets/sounds/coin.wav");

    Mix_PlayMusic(mainMusic, -1);
    Die = 0;
    startTicks = 0;
    score = 0;
    player->dead = false;
    isRunning = true;
    paused = false;
}

void Game::menu(){
    time->Start();

    SDL_RenderClear(renderer);
    SDL_Texture* temp = TextureManager::LoadTexture("assets/images/menu.png");
    SDL_Rect tempR = {64, 64, 352, 210};
    SDL_RenderCopy(renderer, temp, NULL, &tempR);
    SDL_DestroyTexture(temp);

    play->Render();
    quit->Render();
    help->Render();

    SDL_Event e;
    SDL_PollEvent (&e);
    if (e.type == SDL_QUIT) {
        canPlay = true;
        isRunning = false;
        _quit = true;
        loop = false;
    }
    if (!instructions) {
                SDL_Rect playRect = play->GetRect();
                int xm, ym;
                SDL_GetMouseState(&xm, &ym);


                if (TextureManager::MouseCheck(xm, ym, playRect)) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        clicked = true;
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
                        loop = false;
                    }
                    quit->color = {255,255,0};
                }
                else quit->color = {255,255,255};
                SDL_Rect helpRect = help->GetRect();
                if (TextureManager::MouseCheck(xm, ym, helpRect)) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        instructions = true;
                    }
                    help->color = {255,255,0};
                }
                else help->color = {255,255,255};

                if (clicked) {
                    int lvl_x = 352, lvl_y = 260, lvl_w = 110, lvl_h = 32;
                    SDL_Color tempColor = {255,255,255};
                    Text Level_1("Level 1", lvl_x, lvl_y, lvl_w, lvl_h, tempColor, sfont);  
                    lvl_y += 40;
                    Text Level_2("Level 2", lvl_x, lvl_y, lvl_w, lvl_h, tempColor, sfont);
                    SDL_Rect levelR = Level_1.GetRect();
                    if (TextureManager::MouseCheck(xm, ym, levelR)) {
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            canPlay = true;
                            map_no = 1;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        }
                        Level_1.color = {255,255,0};
                    }
                    else Level_1.color = {255,255,255};
                    SDL_Rect _levelR = Level_2.GetRect();
                    if (TextureManager::MouseCheck(xm, ym, _levelR)) {
                        if (e.type == SDL_MOUSEBUTTONDOWN) {
                            canPlay = true;
                            map_no = 2;
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                            
                        }
                        Level_2.color = {255,255,0};
                    }
                    else Level_2.color = {255,255,255};
                    Level_1.Render();
                    Level_2.Render();
                }
            }
    startTicks = time->getTime();

    if (instructions) {
        SDL_RenderClear(renderer);
        SDL_Texture* instruct = TextureManager::LoadTexture("assets/images/instructions.png");
        SDL_RenderCopy(renderer, instruct, NULL, NULL);
        SDL_DestroyTexture(instruct);
        int bx = 345, by = 420, bw = 100, bh = 32;
        SDL_Color backColor = {255,255,255};
        Text back = Text("Back", bx, by, bw, bh, backColor, font);
        int xm = 0, ym = 0;
        SDL_GetMouseState(&xm, &ym);
        SDL_Rect backRect = back.GetRect();
        if (TextureManager::MouseCheck(xm, ym, backRect)) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                instructions = false;
            }
            back.color = {255,255,0};
        }
        else back.color = {255,255,255};
        back.Render();



    }
    SDL_RenderPresent(renderer);
}
void Game::start(){
    if (!loaded) {
        startTicks = time->getTime();
        loaded = true;
    }

    while (time->getTime() - startTicks <= 3000) {

    SDL_Event e;
    SDL_PollEvent (&e);
    if (e.type == SDL_QUIT) {
        _quit = true;
        loop = false;
        startTicks = time->getTime() + 1000;
    }
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

    if (map_no == 1) SDL_SetRenderDrawColor(renderer, 3, 173, 252, 255);
    else if (map_no == 2) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    startTicks = 0;
    loaded = false;
    canMove = false;


}
void Game::handleEvents(){
    SDL_Event e;
    if (canMove) SDL_PollEvent (&e);
    
    if (e.type == SDL_QUIT) {
        isRunning = false;
        _quit = true;
        loop = false;
    }
        
    if (!canMove) {
        player->ResetVel();
        canMove = true;
    }
    if (player->dead) {
        player->ResetVel();
        canMove = false;
    }
    if (canMove) {
        if (e.key.keysym.sym == SDLK_p && e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            paused = !paused;
            if (paused) {
                time->Pause();
                Mix_PauseMusic();
            }
            else {
                time->Unpause();
                Mix_ResumeMusic();
            }
        }
        else {
            {
                if (!player->dead) player->InputHandle(e);
                if (player->space == 16) {
                    if (!paused) Mix_PlayChannel(-1, jump, 0);
                }
            }
            if (paused) {
                if (player->space > 0) player->space = 0;
            }
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
    int x = 10, y = 10, w = 128, h = 32;
    SDL_Color color = {0,0,0};

    if (map_no == 1) SDL_RenderCopy(renderer, background, NULL, NULL);
    else if (map_no == 2) {
        color = {255,255,255};
    }

    std::string temp = "Score: " + std::to_string(score);

    const char* _score = temp.c_str();

    Text text = Text(_score, x, y, w, h, color, font);
    text.Render();


    std::ifstream file;
    file.open("assets/highScore.txt");
    file >> highestScore;
    if (score >= highestScore) highScore(score);

    temp = "Highest score: " + std::to_string(highestScore);
    const char* hScore = temp.c_str();

    x = 288;
    w = 250;
    Text _highScore = Text(hScore, x, y, w, h, color, font);
    _highScore.Render();
    
    for (int i = 0; i < life; i++) heart[i].Render();

    if (!player->won) {
    int _size = ene.size();
    if (player->GetY() >= SCREEN_HEIGHT - 32) player->dead = true;
    for (int i = 0; i < _size; i++) {
        if (ene[i].GetX() < player->x_map + 1100 && ene[i].GetX() > player->x_map - 32) {
            if (ene[i].GetY() >= SCREEN_HEIGHT) ene[i].dead = true;
            if (ene[i].type == 1 && !ene[i].time) {
                if (!paused) ene[i].Move();
            }
            if(!ene[i].dead) ene[i].Render();
            ene[i].SetMap(player->x_map);
            SDL_Rect r = ene[i].GetRect();
            SDL_Rect pr = player->GetRect();

            if (ene[i].type == 1) {

                if (time->getTime() - eneTime[i] >= 500 && ene[i].time) ene[i].dead = true;
                
                if (player->DeadCheck(r) && player->Jumped(r) && player->dead == false && ene[i].dead == false) {
                    if (!ene[i].time) {
                        player->Bounce();
                        eneTime[i] = time->getTime();
                        ene[i].time = true;
                        score++;
                        Mix_PlayChannel(-1, mob, 0);
                    }
                }
                else if (TextureManager::PlayerCollisionChecker(pr, r) && !player->Jumped(r) && ene[i].dead == false && !ene[i].time) {
                    player->dead = true;
                }
            }
            else if (ene[i].type == 5) {
                ene[i].PlantMove();
                ene[i].Move();
                if (ene[i].plantLock) {
                    int delay = 2000;
                    if (!ene[i].time) {
                        eneTime[i] = time->getTime();
                        ene[i].time = true;
                    }
                    else {
                        if (time->getTime() - eneTime[i] >= delay) {
                            ene[i].plantLock = false;
                            if (ene[i].plantY == 0 || ene[i].plantY == -51) ene[i].plantY--;
                            ene[i].time = false;
                        }
                    }
                    if (TextureManager::PlayerCollisionChecker(pr, r)) player->dead = true;
                }
                if (TextureManager::PlayerCollisionChecker(pr, r) && !player->Jumped(r) && ene[i].dead == false && !ene[i].time) {
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

        
        map->DrawMap(map_no);
        map->SetMap(player->x_map);
    if (!paused) {
        if (!player->dead) player->Physics();
        player->ApplyAnimation();
        player->Render();
        player->Move();
        player->CenterMapIndex();
    }
    else {
        player->Render();
        player->CenterMapIndex();
    }

    }
    else {
        if (!endMus){Mix_HaltMusic(); Mix_PlayMusic(endMusic, 0); endMus = true;}

        ene.back().Render();
        ene.back().SetMap(player->x_map);
        ene.back().Flag();

        map->DrawMap(map_no);
        map->SetMap(player->x_map);
        player->ApplyAnimation();
        player->CenterMapIndex();
        if (!player->endtime) {
            player->win();
            startTicks = time->getTime();
        }
        else if (time->getTime() - startTicks >= 1000) {
            victory = true;
            startTicks = time->getTime();
            SDL_SetRenderDrawColor(renderer, 0,0,0,0);
        }

    }

if (paused) {
        SDL_Texture* tex = NULL;
        tex = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 800, 480 );
        SDL_Rect rec;
        rec.x = 200;
        rec.y = 120;
        rec.w = 400;
        rec.h = 120;
        SDL_RenderCopy(renderer, tex, NULL, &rec);
        SDL_DestroyTexture(tex);
        int px = 280, py = 160, pw = 256, ph = 32;
        SDL_Color pColor = {255,255,255,255};
        Text pauseText("Press 'P' to resume", px, py, pw, ph, pColor, font);
        pauseText.Render();
    }

    SDL_RenderPresent(renderer);
};
void Game::die(){
    if (Die == 2) {
        startTicks = time->getTime();
        Die = 3;
    }
    if (Die == 3) {
        if (time->getTime() - startTicks >= 4000) {
            Die = -1;
            if (player->playing == false) {
                if (true) {
                    isRunning = false;
                    player->playing = true;
                    life--;
                    player->SetPos();
                    canPlay = false;
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
    free(help);

    Mix_FreeMusic(mainMusic);
    Mix_FreeMusic(deadMusic);
    Mix_FreeMusic(endMusic);
    Mix_FreeMusic(closeMusic);
    Mix_FreeChunk(jump);
    Mix_FreeChunk(mob);
    Mix_FreeChunk(coin);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(background);
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
    int x = 0, y = 0, w = 0, h = 36;
    SDL_Color color = {255,255,255};
    SDL_Event e;
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
        endGame = true;
        loop = false;
    }
    if (!close) {
        Mix_PlayMusic(closeMusic, 0);
        close = true;
    }
    if (victory) {
        /*while (time->getTime() - startTicks <= 10000)*/ {
            x = 340, y = 210, w = 128, h = 36;
            color = {255,255,255};
            Text the_end = Text("You won!",x ,y, w, h, color, font);
            the_end.Render();
            std::string temp = "Score: " + std::to_string(score);
            const char* _score = temp.c_str();
            y += 40;
            Text score = Text(_score, x, y, w, h, color, font);
            score.Render();
            
        }
    }
    else {
        /*while (time->getTime() - startTicks <= 10000)*/ {
            x = 340, y = 220, w = 128, h = 32;
            color = {255,255,255};
            Text the_end = Text("You lose!",x , y, w, h, color, font);
            the_end.Render();
            
        }
    }

    x = 150, y = 350, w = 192, h = 32;
    Text play_again = Text ("Play again?", x, y, w, h, color, font);
    x = 360; w = 64;
    Text yes = Text ("Yes", x, y, w, h, color, sfont);
    x = 480; w = 64;
    Text no = Text ("No", x, y, w, h, color, sfont);

    int xm = 0, ym = 0;
    SDL_GetMouseState(&xm, &ym);
    SDL_Rect yesR = yes.GetRect();
    SDL_Rect noR = no.GetRect();
    if (TextureManager::MouseCheck(xm, ym, yesR)) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            endGame = true;
            life = 3;
            clicked = false;
            victory = false;
            canPlay = false;
            player->endtime = false;
            player->won = false;
            player->SetPos();
            SDL_SetRenderDrawColor(renderer, 3, 173, 252, 255);
            
        }
        yes.color = {255,255,0};
    }
    else yes.color = {255,255,255};

    if (TextureManager::MouseCheck(xm, ym, noR)) {
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            endGame = true;
            loop = false;
        }
        no.color = {255,255,0};
    }
    else no.color = {255,255,255};

    play_again.Render();
    yes.Render();
    no.Render();

    SDL_RenderPresent(renderer);
}

void Game::highScore(int &score){
    std::ofstream file;
    file.open("assets/highScore.txt");
    file.clear();
    file << score;
    file.close();
}
