#pragma once
#include "Game.h"
#include <string>
class Map {
public:
    Map();
    ~Map();
    void LoadMap(int map[16][224]);
    void DrawMap();
    void RefreshMap();
    static int level_1[16][224];
    static SDL_Rect GetBox(int i, int j);
    void SetMap(const int &x);
private:
    SDL_Rect src, dest;
//    SDL_Texture* brick;
//    SDL_Texture* ground;
//    SDL_Texture* pipe_left_bot;
//    SDL_Texture* pipe_left_top;
//    SDL_Texture* pipe_right_bot;
//    SDL_Texture* pipe_right_top;
    std::vector <SDL_Texture*> obstacleTex;
    int map[16][224];
    int xmap, ymap;
    int x_start = 0, y_start = 0;
    std::vector<const char*> files;
};
