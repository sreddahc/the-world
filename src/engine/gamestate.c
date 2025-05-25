#include "gamestate.h"
#include "maths.h"

 
static TW_GameState* gameState = NULL;


// Create a game timer to be used globally by all objects.
void TW_GameState_Create()
{
    gameState = malloc( sizeof( TW_GameState ) );
    gameState->deltaTime = 0.0;
    gameState->now = 0;
    gameState->previous = 0;
    gameState->ms = SDL_GetTicks64();
    gameState->frame = 0;
    gameState->frameCap = 0;
    gameState->ticksPerFrame = 0;
    gameState->paused = false;
    // This needs to be changed
    gameState->screenSize = TW_Vector2_Create( 600, 480 );
}


// Free resources used by the game state.
void TW_GameState_Free()
{
    gameState->frame = 0;
    gameState->ms = 0;
    gameState->previous = 0;
    gameState->now = 0;
    gameState->deltaTime = 0.0;
    gameState->paused = false;
    TW_Vector2_Free( gameState->screenSize );
    gameState->screenSize = NULL;
    free( gameState );
}


// Update the game timer. This should be called once every cycle of the main loop.
void TW_GameState_Update()
{
    gameState->ms = SDL_GetTicks64();
    gameState->frame++;
    gameState->now = SDL_GetPerformanceCounter();
    gameState->deltaTime = (float)( gameState->now - gameState->previous ) / (float)SDL_GetPerformanceFrequency();
    if( gameState->deltaTime >= TIME_DELTA_CAP )
    {
        gameState->deltaTime = 0.0;
    }
    gameState->previous = gameState->now;
}


// Get the current time delta.
float TW_GameState_GetDeltaTime()
{
    return gameState->deltaTime;
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


// Get the current time in ms.
Uint64 TW_GameState_GetTime()
{
    return gameState->ms;
}


// Get the current pause status of the game.
bool TW_GameState_PauseStatus()
{
    return gameState->paused;
}


// Pause the game.
void TW_GameState_Pause()
{
    gameState->paused = true;
}


// Unpause/resume the game.
void TW_GameState_Resume()
{
    gameState->paused = false;
}


// Get Screen Size
TW_Vector2* TW_GameState_GetScreenSize()
{
    return gameState->screenSize;
}