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


void TW_Listener_Add( enum TW_ListenerType type, void* value )
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
}
