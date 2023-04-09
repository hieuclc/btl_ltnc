#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
class Game {
private:
    bool isRunning;
    SDL_Window* window;


public:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 480;
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void inputHandle(SDL_Event e);
    bool running(){
        return isRunning;
    };
    static SDL_Renderer* renderer;
};

#endif // Game_h
