#include "gametimer.h"

 
static TW_GameTimer* gameTimer = NULL;


void TW_GameTimer_Create()
{
    gameTimer = malloc( sizeof( TW_GameTimer ) );
    gameTimer->delta_time = 0.0;
    gameTimer->now = 0;
    gameTimer->previous = 0;
}


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


float TW_GameTimer_GetTimeDelta()
{
    return gameTimer->delta_time;
}


void TW_GameTimer_Free()
{
    gameTimer->previous = 0;
    gameTimer->now = 0;
    gameTimer->delta_time = 0.0;
    free(gameTimer);
}