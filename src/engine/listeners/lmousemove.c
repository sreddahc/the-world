#include "../listener.h"


// Creates a listener object that checks for mouse-move events.
TW_L_MouseMove* TW_L_MouseMove_Create()
{
    TW_L_MouseMove* listener = malloc( sizeof( TW_L_MouseMove ) );
    listener->eventExists = false;
    return listener;
}


// Frees the resources used by a mouse-move listener object.
void TW_L_MouseMove_Free( TW_L_MouseMove* self )
{
    self->eventExists = false;
    free( self );
}


// If a mouse-move event has been registered - update the listener object.
void TW_L_MouseMove_Check( TW_L_MouseMove* self, SDL_Event event )
{
    if( event.type == SDL_MOUSEMOTION )
    {
        self->eventExists = true;
    }
}


// Clear the mouse-move listener object so no events are registered.
void TW_L_MouseMove_Clear( TW_L_MouseMove* self )
{
    self->eventExists = false;
}
