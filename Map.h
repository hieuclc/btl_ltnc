#pragma once
#include "Game.h"
#include <string>
class Map {
public:
    Map();
    ~Map();
    void LoadMap(int map[15][224]);
    void DrawMap();
    void RefreshMap();
    static int level_1[15][224];
    void SetMap(const int &x);


private:
    SDL_Rect src, dest;
    //std::vector <SDL_Texture*> obstacleTex;
    int map[15][224];
    int xmap, ymap;
    int x_start = 0, y_start = 0;
    std::vector<const char*> files;
    SDL_Rect pics[17];
};
