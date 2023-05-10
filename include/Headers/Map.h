#pragma once
#include "Game.h"
#include <string>
class Map {
public:
    Map();
    ~Map();
    void LoadMap(int map[15][224]);
    void DrawMap(int num);
    static int level_1[15][224];
    static int level_2[15][224];
    static int game_map[15][224];
    void SetMap(const int &x);


private:
    SDL_Rect src, dest;
    int map[15][224];
    int xmap, ymap;
    int x_start = 0, y_start = 0;
    std::vector<const char*> files;
    SDL_Rect pics[20];
};
