#include "gametimer.h"

 
static TW_GameTimer* gameTimer = NULL;


// Create a game timer to be used globally by all objects.
void TW_GameTimer_Create()
{
    gameTimer = malloc( sizeof( TW_GameTimer ) );
    gameTimer->delta_time = 0.0;
    gameTimer->now = 0;
    gameTimer->previous = 0;
    gameTimer->ms = SDL_GetTicks64();
    gameTimer->frame = 0;
    gameTimer->frameCap = 0;
    gameTimer->ticksPerFrame = 0;
}


// Update the game timer. This should be called once every cycle of the main loop.
void TW_GameTimer_Update()
{
    gameTimer->ms = SDL_GetTicks64();
    gameTimer->frame++;
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


// Get the current time delta between now and the last time the game timer was updated.
float TW_GameTimer_GetFPS()
{
    float fps = gameTimer->frame / ( gameTimer->ms / MILLISECONDS_IN_A_SEC );
    
    if( fps > FPS_FRAME_CAP )
    {
        return 0.0;
    }

    return ;
}


// Given a Frame Per Second limit, limit the frame rate.
void TW_GameTimer_SetFrameLimit( int fps )
{
    gameTimer->ticksPerFrame = (int)( 1000 / fps );
}


// If there is a frame cap set, delay the next frame to limit the frame rate.
void TW_GameTimer_LimitFrameRate()
{
    int frameTicks = TW_GameTimer_GetFPS();
    if( gameTimer->frameCap != 0 )
    {
        if( frameTicks < gameTimer->ticksPerFrame )
        {
            SDL_Delay( gameTimer->ticksPerFrame - frameTicks );
        }
    }
}


// Free resources used by the game timer.
void TW_GameTimer_Free()
{
    gameTimer->frame = 0;
    gameTimer->ms = 0;
    gameTimer->previous = 0;
    gameTimer->now = 0;
    gameTimer->delta_time = 0.0;
    free(gameTimer);
}