#include "gamestate.h"

 
static TW_GameState* gameState = NULL;


// Create a game timer to be used globally by all objects.
void TW_GameState_Create()
{
    gameState = malloc( sizeof( TW_GameState ) );
    gameState->delta_time = 0.0;
    gameState->now = 0;
    gameState->previous = 0;
    gameState->ms = SDL_GetTicks64();
    gameState->frame = 0;
    gameState->frameCap = 0;
    gameState->ticksPerFrame = 0;
}


// Update the game timer. This should be called once every cycle of the main loop.
void TW_GameState_Update()
{
    gameState->ms = SDL_GetTicks64();
    gameState->frame++;
    gameState->now = SDL_GetPerformanceCounter();
    gameState->delta_time = (float)( gameState->now - gameState->previous ) / (float)SDL_GetPerformanceFrequency();
    if( gameState->delta_time >= TIME_DELTA_CAP )
    {
        gameState->delta_time = 0.0;
    }
    gameState->previous = gameState->now;
}


// Get the current time delta.
float TW_GameState_GetTimeDelta()
{
    return gameState->delta_time;
}


// Get the current time delta between now and the last time the game timer was updated.
float TW_GameState_GetFPS()
{
    float fps = (float)gameState->frame / ( (float)gameState->ms / MILLISECONDS_IN_A_SEC );
    
    if( fps > FPS_FRAME_CAP )
    {
        return 0.0;
    }

    return fps;
}


// Given a Frame Per Second limit, limit the frame rate.
void TW_GameState_SetFrameLimit( int fps )
{
    gameState->ticksPerFrame = (int)( 1000 / fps );
}


// If there is a frame cap set, delay the next frame to limit the frame rate.
void TW_GameState_LimitFrameRate()
{
    int frameTicks = TW_GameState_GetFPS();
    if( gameState->frameCap != 0 )
    {
        if( frameTicks < gameState->ticksPerFrame )
        {
            SDL_Delay( gameState->ticksPerFrame - frameTicks );
        }
    }
}


Uint64 TW_GameState_GetTime()
{
    return gameState->ms;
}


// Free resources used by the game state.
void TW_GameState_Free()
{
    gameState->frame = 0;
    gameState->ms = 0;
    gameState->previous = 0;
    gameState->now = 0;
    gameState->delta_time = 0.0;
    free( gameState );
}
