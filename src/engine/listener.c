#include "listener.h"


// Create a listener object to listen for events.
TW_Listener* TW_Listener_Create()
{
    TW_Listener* listener = malloc( sizeof( TW_Listener ) );
    return listener;
}


// Free the resources used by a listener object.
void TW_Listener_Free( TW_Listener* self )
{
    switch ( self->type )
    {
        case TW_L_KEYDOWN:
            TW_L_KeyDown_Free( self->keydown );
            break;

        case TW_L_QUIT:
            TW_L_Quit_Free( self->quit );
            break;
        
        default:
            break;
    }
    free( self );
}


TW_Listener* TW_Listener_Add( enum TW_ListenerType type, void* value )
{
    // Check if listener already exists... this code needs to  be inserted...
    // If not:
    TW_Listener* newListener = TW_Listener_Create();
    newListener->type = type;
    switch ( type )
    {
        case TW_L_KEYDOWN:
            newListener->keydown = value;
            break;

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
    TW_Listener* listener = value;
    switch ( type )
    {
        case TW_L_KEYDOWN:
            TW_L_KeyDown_Check( listener->keydown, event );
            break;

        case TW_L_QUIT:
            TW_L_Quit_Check( listener->quit, event );
            break;
        
        default:
            break;
    }
}



void TW_Listener_Clear( TW_Listener* self )
{
    switch ( self->type )
    {
        case TW_L_KEYDOWN:
            TW_L_KeyDown_Clear( self->keydown );
            break;

        case TW_L_QUIT:
            TW_L_Quit_Clear( self->quit );
            break;
        
        default:
            break;
    }
}