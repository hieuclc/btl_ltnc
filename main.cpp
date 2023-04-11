#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_mixer.h>
#include "Game.h"
#include "Music.h"
using namespace std;




Game *game = nullptr;
const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;
int life = 3;
int main(int argc, char* argv[])
{
        game = new Game();
        game->init("demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, false);
        while (game->running()) {
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
        //delete (game);
    game->clean();
    return 0;
}
