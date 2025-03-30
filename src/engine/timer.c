#include <stdio.h>
#include <SDL2/SDL.h>
#include "timer.h"

// Instantiate the TW_Timer object.
void TW_Timer_Init( TW_Timer* self, bool paused )
{
    self->currentTime = SDL_GetTicks();
    self->paused = paused;
    self->pauseTime = self->currentTime;
    self->pauseDuration = 0;
}

// Resets a TW_Timer object without changing the state.
void TW_Timer_Reset( TW_Timer* self )
{
    TW_Timer_Init( self, self->paused );
}

// Pause an unpaused TW_Timer object.
void TW_Timer_Pause( TW_Timer* self )
{
    if( !( self->paused ) )
    {
        self->paused = true;
        self->pauseTime = SDL_GetTicks();
    }
}

// Resume a paused TW_Timer object.
void TW_Timer_Resume( TW_Timer* self )
{
    if( self->paused )
    {
        self->paused = false;
        self->pauseDuration += SDL_GetTicks() - self->pauseTime;
    }
}

// Get the current time of a TW_Timer object.
Uint64 TW_Timer_GetTime( TW_Timer* self )
{
    if( self->paused )
    {
        return ( SDL_GetTicks() - self->currentTime ) - ( SDL_GetTicks() - self->pauseTime ) - self->pauseDuration;
    }
    else
    {
        return SDL_GetTicks() - self->currentTime - self->pauseDuration;
    }
}