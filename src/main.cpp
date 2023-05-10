#include <SDL.h>
#include "Game.h"
using namespace std;

const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

bool pause = false;

int main(int argc, char* argv[])
{
    Game game;
    game.init("Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, false);
    while (game.loop) {
        while(!game.canPlay && !game._quit) {
            game.menu();
        }
        while(game.life > 0 && !game._quit && !game.victory) {
            //game.life = life + 1;
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

        while (!game.endGame && !game._quit) {
            game.end();
        }
    }

    game.clean();
    return 0;
}
