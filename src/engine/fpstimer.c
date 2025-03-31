#include "fpstimer.h"

#include <SDL2/SDL.h>

// Initialise TW_FPSTimer.
void TW_FPSTimer_Init( TW_FPSTimer* self )
{
    self->ms = 0;
    self->frame = 0;
}

// To stay accurate this must be updated every frame.
void TW_FPSTimer_Update( TW_FPSTimer* self )
{
    self->ms = SDL_GetTicks();
    self->frame++;
}

// Returns the current FPS.
float TW_FPSTimer_GetFPS( TW_FPSTimer* self )
{
    if( self->frame / ( self->ms / MILLISECONDS_IN_A_SEC ) > FRAME_CAP ){
        return 0.0;
    }
    else
    {
        return self->frame / ( self->ms / MILLISECONDS_IN_A_SEC );
    }
}

// Free resources used by TW_FPSTimer.
void TW_FPSTimer_Free( TW_FPSTimer* self )
{
    self->ms = 0;
    self->frame = 0;
}