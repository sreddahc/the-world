#include "listener.h"


// Create a listener object to listen for events.
TW_Listener* TW_Listener_Create()
{
    TW_Listener* listener = malloc( sizeof( TW_Listener ) );
    listener->event = false;
    return listener;
}


// Free the resources used by a listener object.
void TW_Listener_Free( TW_Listener* self )
{
    self->event = false;
    free( self );
}


TW_Listener* TW_Listener_Add( enum TW_ListenerType type, void* value )
{
    // Check if listener already exists... this code needs to  be inserted...
    // If not:
    TW_Listener* newListener = TW_Listener_Create();
    newListener->type = type;
    newListener->event = false;
    switch ( type )
    {
    case TW_L_QUIT:
        newListener->quit = value;
        break;
    
    default:
        break;
    }

    return newListener;
}


void TW_Listener_Check( enum TW_ListenerType type, void* value, SDL_Event event )
{
    // printf( "quit was set! %d \n", type );
    TW_Listener* currentListener = value;
    switch ( type )
    {
    case TW_L_QUIT:
        currentListener->event = TW_L_Quit_Check( currentListener->quit, event );
        break;
    
    default:
        break;
    }
}