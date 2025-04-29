#include "../listener.h"


// Create a key-down listener object.
TW_L_KeyDown* TW_L_KeyDown_Create( SDL_KeyCode key )
{
    TW_L_KeyDown* listener = malloc( sizeof( TW_L_KeyDown ) );
    listener->eventExists = false;
    listener->key = key;
    return listener;
}


// Frees the resources used by a key-down listener object.
void TW_L_KeyDown_Free( TW_L_KeyDown* self )
{
    self->eventExists = false;
    self->key = 0;
    free( self );
}


// Check to see if a key-down event has been registered for the key in this key-down listener object.
void TW_L_KeyDown_Check( TW_L_KeyDown* self, SDL_Event event )
{
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
    {
        if( event.key.keysym.sym == self->key )
        {
            self->eventExists = true;
        }
    }
}


// Clears the key-down listener object so no events are registered.
void TW_L_KeyDown_Clear( TW_L_KeyDown* self )
{
    self->eventExists = false;
}