#include <iostream>
#include <stdio.h>
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
#include "Game.h"
//#include "Music.h"
using namespace std;




//Game game = nullptr;
const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;
int life = 3;
int main(int argc, char* argv[])
{
    Game game;
    game.init("Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, false);
    while(!game.canPlay && !game._quit) {
        game.menu();
    }
    while(life-- && !game._quit) {
        game.life = life + 1;
        if (!game.victory) {
            if (!game._quit) {
                game.load();
                game.start();
                while (game.running() && !game.victory) {
                    frameStart = SDL_GetTicks();
                    game.handleEvents();
                    game.update();
                    game.render();
                    frameTime = SDL_GetTicks() - frameStart;
                    if (frameDelay > frameTime) {
                        SDL_Delay(frameDelay - frameTime);
                    }
                    game.die();
                }
            }
        }

    }
    game.blackScreen();
    if (!game._quit) game.end();

    game.clean();
    return 0;
}
