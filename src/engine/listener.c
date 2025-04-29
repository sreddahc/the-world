#include "listener.h"


// Create a listener object to listen for events
TW_Listener* TW_Listener_Create()
{
    TW_Listener* listener = malloc( sizeof( TW_Listener ) );
    return listener;
}


// Free the resources used by a listener object
void TW_Listener_Free( TW_Listener* self )
{
    switch ( self->type )
    {
        case TW_L_KEYDOWN:
            TW_L_KeyDown_Free( self->keyDown );
            break;

        case TW_L_KEYUP:
            TW_L_KeyUp_Free( self->keyUp );
            break;

        case TW_L_MOUSEMOVE:
            TW_L_MouseMove_Free( self->mouseMove );
            break;

        case TW_L_QUIT:
            TW_L_Quit_Free( self->quit );
            break;

        default:
            break;
    }
    free( self );
}


// Add a listener of a given type
TW_Listener* TW_Listener_Add( enum TW_ListenerType type, void* value )
{
    TW_Listener* newListener = TW_Listener_Create();
    newListener->type = type;
    switch ( type )
    {
        case TW_L_KEYDOWN:
            newListener->keyDown = value;
            break;

        case TW_L_KEYUP:
            newListener->keyUp = value;
            break;

        case TW_L_MOUSEMOVE:
            newListener->mouseMove = value;
            break;

        case TW_L_QUIT:
            newListener->quit = value;
            break;
        
        default:
            break;
    }

    return newListener;
}


// Check an SDL event against against a listener
void TW_Listener_Check( enum TW_ListenerType type, TW_Listener* listener, SDL_Event event )
{
    switch ( type )
    {
        case TW_L_KEYDOWN:
            TW_L_KeyDown_Check( listener->keyDown, event );
            break;

        case TW_L_KEYUP:
            TW_L_KeyUp_Check( listener->keyUp, event );
            break;

        case TW_L_MOUSEMOVE:
            TW_L_MouseMove_Check( listener->mouseMove, event );
            break;

        case TW_L_QUIT:
            TW_L_Quit_Check( listener->quit, event );
            break;
        
        default:
            break;
    }
}


// Clear the state of a given listener such that it has no events
void TW_Listener_Clear( TW_Listener* self )
{
    switch ( self->type )
    {
        case TW_L_KEYDOWN:
            TW_L_KeyDown_Clear( self->keyDown );
            break;

        case TW_L_KEYUP:
            TW_L_KeyUp_Clear( self->keyUp );
            break;
        
        case TW_L_MOUSEMOVE:
            TW_L_MouseMove_Clear( self->mouseMove );
            break;

        case TW_L_QUIT:
            TW_L_Quit_Clear( self->quit );
            break;
        
        default:
            break;
    }
}