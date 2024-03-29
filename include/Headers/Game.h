#ifndef Game_h
#define Game_h
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
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
    static bool paused;
    bool getPausedState(){return paused;};
    bool running(){
        return isRunning;
    };
    static SDL_Renderer* renderer;
    bool instructions; 
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
    bool loop = true;
    bool endGame = true;
    bool canMove = true;
    //bool tryAgain();
    bool clicked = false;
    bool loaded = false;
    int map_no;

    int highestScore = 0;
    void highScore(int &score);
};

#endif // Game_h
