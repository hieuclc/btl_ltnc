#ifndef Game_h
#define Game_h
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
class Game {
private:
    bool isRunning;
    SDL_Window* window = NULL;


public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 480;
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void load();
    void end();
    void handleEvents();
    void update();
    void render();
    void clean();
    bool _quit;
    bool running(){
        return isRunning;
    };
    static SDL_Renderer* renderer;
    bool canPlay;
    int life;
    int score = 0;
    void menu();
    void start();
    void die();
    void blackScreen(){SDL_SetRenderDrawColor(renderer, 0,0,0,0);};
    bool victory;
    bool endMus;
    bool close;
};

#endif // Game_h
