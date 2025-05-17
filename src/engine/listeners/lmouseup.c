#include "../listener.h"


// Creates a listener that checks mouse-up events for a button.
TW_L_MouseUp* TW_L_MouseUp_Create( Uint8 button )
{
    TW_L_MouseUp* listener = malloc( sizeof( TW_L_MouseUp ) );
    listener->eventExists = false;
    listener->button = button;
    return listener;
}


// Frees the resources used by a mouse-up listener object.
void TW_L_MouseUp_Free( TW_L_MouseUp* self )
{
    self->eventExists = false;
    self->button = 0;
    free( self );
}


// If a mouse-up event has been registered - update the listener object.
void TW_L_MouseUp_Check( TW_L_MouseUp* self, SDL_Event event )
{
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == self->button )
        {
            self->eventExists = true;
        }
    }
}


// Clear the mouse-up listener object so no events are registered.
void TW_L_MouseUp_Clear( TW_L_MouseUp* self )
{
    self->eventExists = false;
}
