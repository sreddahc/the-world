#include "../listener.h"


// Creates a listener object that checks for quit events.
TW_L_Quit* TW_L_Quit_Create()
{
    TW_L_Quit* listener = malloc( sizeof( TW_L_Quit ) );
    listener->quit = false;
    return listener;
}


// Frees the resources used by a quit listener object.
void TW_L_Quit_Free( TW_L_Quit* self )
{
    self->quit = false;
    free( self );
}


// If a quit event has been registered and updates the listener object.
bool TW_L_Quit_Check( TW_L_Quit* self, SDL_Event event )
{
    if( event.type == SDL_QUIT )
    {
        self->quit = true;
    }
    return self->quit;
}


// Clears the quit listener object so no events are registered.
void TW_L_Quit_Clear( TW_L_Quit* self )
{
    self->quit = false;
}