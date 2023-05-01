#pragma once
#include "Game.h"
#include "TextureManager.h"
#include <SDL_mixer.h>

class Music {
public:
    Music();
    ~Music();
    void InputHandle(SDL_Event &e);
    void Close();

    Mix_Music *mainMusic = NULL;
    Mix_Chunk *jump = NULL;

private:
    int song;


};
