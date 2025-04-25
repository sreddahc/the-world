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
