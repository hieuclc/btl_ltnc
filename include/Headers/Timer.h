#pragma once
#include "Game.h"
class Timer {
public:
    Timer();
    ~Timer();
    static bool paused;
    static bool started;

    void Start();
    void Stop();
    void Pause();
    void Unpause();
    Uint32 getTime();

private:
    Uint32 startTicks;
    Uint32 pausedTicks;

};