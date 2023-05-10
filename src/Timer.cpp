#include "Timer.h"

bool Timer::paused = false;
bool Timer::started = false;

Timer::Timer(){
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

Timer::~Timer(){};

void Timer::Start(){
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::Stop(){
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::Pause(){
    if (started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::Unpause(){
    if (started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Timer::getTime(){
    Uint32 time = 0;
    if (started) {
        if (!paused) time = SDL_GetTicks() - startTicks;
        else time = pausedTicks;
    }
    return time;
}