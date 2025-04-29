#include "../listener.h"


// Create a key-up listener object.
TW_L_KeyUp* TW_L_KeyUp_Create( SDL_KeyCode key )
{
    TW_L_KeyUp* listener = malloc( sizeof( TW_L_KeyUp ) );
    listener->eventExists = false;
    listener->key = key;
    return listener;
}


// Frees the resources used by a key-up listener object.
void TW_L_KeyUp_Free( TW_L_KeyUp* self )
{
    self->eventExists = false;
    self->key = 0;
    free( self );
}


// Check to see if a key-up event has been registered for the key in this key-up listener object.
void TW_L_KeyUp_Check( TW_L_KeyUp* self, SDL_Event event )
{
    if( event.type == SDL_KEYUP && event.key.repeat == 0 )
    {
        if( event.key.keysym.sym == self->key )
        {
            self->eventExists = true;
        }
    }
}


// Clears the key-up listener object so no events are registered.
void TW_L_KeyUp_Clear( TW_L_KeyUp* self )
{
    self->eventExists = false;
}