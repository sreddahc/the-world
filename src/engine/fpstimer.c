#include "fpstimer.h"

#include <SDL2/SDL.h>

// Initialises a TW_FPSTimer object.
void TW_FPSTimer_Init( TW_FPSTimer* self )
{
    self->ms = 0;
    self->frame = 0;
}

// Updates a TW_FPSTimer object with the current frame count and time.
// This must be done every frame to remain accurate.
void TW_FPSTimer_Update( TW_FPSTimer* self )
{
    self->ms = SDL_GetTicks();
    self->frame++;
}

// Get the current number of Frames Per Second (FPS) as a float.
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

// Frees resources used by a TW_FPSTimer object.
void TW_FPSTimer_Free( TW_FPSTimer* self )
{
    self->ms = 0;
    self->frame = 0;
}
