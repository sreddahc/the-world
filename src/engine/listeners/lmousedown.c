#include "../listener.h"


// Creates a listener object that checks for mouse-down events.
TW_L_MouseDown* TW_L_MouseDown_Create()
{
    TW_L_MouseDown* listener = malloc( sizeof( TW_L_MouseDown ) );
    listener->eventExists = false;
    return listener;
}


// Frees the resources used by a mouse-down listener object.
void TW_L_MouseDown_Free( TW_L_MouseDown* self )
{
    self->eventExists = false;
    free( self );
}


// If a mouse-down event has been registered - update the listener object.
void TW_L_MouseDown_Check( TW_L_MouseDown* self, SDL_Event event )
{
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        self->eventExists = true;
    }
}


// Clear the mouse-down listener object so no events are registered.
void TW_L_MouseDown_Clear( TW_L_MouseDown* self )
{
    self->eventExists = false;
}
