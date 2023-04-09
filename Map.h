#pragma once
#include "Game.h"

class Map {
public:
    Map();
    ~Map();
    void LoadMap(int map[15][224]);
    void DrawMap();
    static int level_1[15][224];
    static SDL_Rect GetBox(int i, int j);
    void SetMap(const int &x, const int &y);
private:
    SDL_Rect src, dest;
    SDL_Texture* brick;
    SDL_Texture* ground;
    SDL_Texture* pipe_left_bot;
    SDL_Texture* pipe_left_top;
    SDL_Texture* pipe_right_bot;
    SDL_Texture* pipe_right_top;
    SDL_Texture* obstacle[20];
    int map[16][224];
    int xmap, ymap;
    int x_start = 0, y_start = 0;
};
