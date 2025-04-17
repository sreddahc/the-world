#include "gametimer.h"

 
static TW_GameTimer* gameTimer = NULL;


// Create a game timer to be used globally by all objects.
void TW_GameTimer_Create()
{
    gameTimer = malloc( sizeof( TW_GameTimer ) );
    gameTimer->delta_time = 0.0;
    gameTimer->now = 0;
    gameTimer->previous = 0;
}


// Update the game timer. This should be called once every cycle of the main loop.
void TW_GameTimer_Update()
{
    gameTimer->now = SDL_GetPerformanceCounter();
    gameTimer->delta_time = (float)( gameTimer->now - gameTimer->previous ) / (float)SDL_GetPerformanceFrequency();
    if( gameTimer->delta_time >= TIME_DELTA_CAP )
    {
        gameTimer->delta_time = 0;
    }
    gameTimer->previous = gameTimer->now;
}


// Get the current time delta.
float TW_GameTimer_GetTimeDelta()
{
    return gameTimer->delta_time;
}


// Free resources used by the game timer.
void TW_GameTimer_Free()
{
    gameTimer->previous = 0;
    gameTimer->now = 0;
    gameTimer->delta_time = 0.0;
    free(gameTimer);
}