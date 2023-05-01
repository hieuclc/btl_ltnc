#include "Music.h"
#include <iostream>
Music::Music(){
    mainMusic = Mix_LoadMUS("assets/sounds/bkg_music.wav");
    jump = Mix_LoadWAV("assets/sounds/jump.wav");
    std::cout << mainMusic << std::endl;
};
Music::~Music(){};

void Music::InputHandle(SDL_Event &e){

};

void Music::Close(){
    Mix_FreeMusic(mainMusic);
    Mix_FreeChunk(jump);
}
