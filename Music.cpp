#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

Mix_Music *gMusic = NULL;
bool music_init()
{
    bool success = true;
    if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
	return success;
}

bool loadMusic()
{
	bool success = true;
	gMusic = Mix_LoadMUS("drugs/beat.wav");
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	return success;
}
bool playMusic()
{
    bool success = true;
    Mix_PlayMusic(gMusic, -1);
    return success;
}
void music_close()
{
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
	Mix_Quit();
}
void music_all(){
    music_init();
    loadMusic();
    playMusic();
}


