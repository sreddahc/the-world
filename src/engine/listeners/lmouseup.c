#include "../listener.h"


// Creates a listener object that checks for mouse-up events.
TW_L_MouseUp* TW_L_MouseUp_Create()
{
    TW_L_MouseUp* listener = malloc( sizeof( TW_L_MouseUp ) );
    listener->eventExists = false;
    return listener;
}


// Frees the resources used by a mouse-up listener object.
void TW_L_MouseUp_Free( TW_L_MouseUp* self )
{
    self->eventExists = false;
    free( self );
}


// If a mouse-up event has been registered - update the listener object.
void TW_L_MouseUp_Check( TW_L_MouseUp* self, SDL_Event event )
{
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        self->eventExists = true;
    }
}


// Clear the mouse-up listener object so no events are registered.
void TW_L_MouseUp_Clear( TW_L_MouseUp* self )
{
    self->eventExists = false;
}
