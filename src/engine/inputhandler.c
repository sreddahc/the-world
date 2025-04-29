#include "inputhandler.h"


static TW_InputHandler* inputHandler = NULL;


// Create the input handler. There is one in the game. No inputs are processed if it is not created.
void TW_InputHandler_Create()
{
    inputHandler = malloc( sizeof( TW_InputHandler ) );
    inputHandler->eventsExist = 0;
    inputHandler->size = 0;
    inputHandler->listeners = NULL;
}


// Free the resources used by the InputHandler.
void TW_InputHandler_Free()
{
    inputHandler->eventsExist = 0;
    for( int index = 0; index < inputHandler->size; index++ )
    {
        TW_Listener_Free( inputHandler->listeners[ index ] );
    }
    inputHandler->size = 0;
    free( inputHandler );
}


// Poll for an event.
bool TW_InputHandler_CheckEvents()
{
    if( inputHandler->eventsExist != 0 )
    {
        return true;
    }
    return false;
}


// Check if there are events to process.
bool TW_InputHandler_Poll()
{
    inputHandler->eventsExist = SDL_PollEvent( &inputHandler->events );
    return TW_InputHandler_CheckEvents();
}

// -- REVIEW BELOW

bool TW_InputHandler_CheckMouse()
{
    if( TW_InputHandler_CheckEvents() == true )
    {
        if
        (
            inputHandler->events.type == SDL_MOUSEMOTION ||
            inputHandler->events.type == SDL_MOUSEBUTTONDOWN ||
            inputHandler->events.type == SDL_MOUSEBUTTONUP
        )
        {
            return true;
        }
    }
    return false;
}


bool TW_InputHandler_CheckMousePressed()
{
    if( TW_InputHandler_CheckMouse() == true )
    {
        if( inputHandler->events.type == SDL_MOUSEBUTTONDOWN )
        {
            return true;
        }
    }
    return false;
}


bool TW_InputHandler_CheckMouseDepressed()
{
    if( TW_InputHandler_CheckMouse() == true )
    {
        if( inputHandler->events.type == SDL_MOUSEBUTTONUP )
        {
            return true;
        }
    }
    return false;
}


// Add a listener to the input handler.
void TW_InputHandler_AddListener( TW_Listener* listener )
{
    inputHandler->size += 1;
    if( inputHandler->size > 0 )
    {
        if( inputHandler->listeners == NULL )
        {
            inputHandler->listeners = malloc( inputHandler->size * sizeof( TW_Listener ) );
            inputHandler->listeners[ inputHandler->size - 1 ] = listener;
        }
        else
        {
            TW_Listener** oldListeners = inputHandler->listeners;
            inputHandler->listeners = malloc( inputHandler->size * sizeof( TW_Listener ) );
            memcpy( inputHandler->listeners, oldListeners, ( inputHandler->size - 1 ) * sizeof( TW_Listener ) );
            free( oldListeners );
            inputHandler->listeners[ inputHandler->size - 1 ] = listener;
        }
    }
}


// Retrieve a listener of the specified type.
TW_Listener* TW_InputHandler_GetListenerType( enum TW_ListenerType type )
{
    TW_Listener* listener = NULL;
    for( int index = 0; index < inputHandler->size; index++ )
    {
        if( inputHandler->listeners[ index ]->type == type )
        {
            listener = inputHandler->listeners[ index ];
        }
    }
    return listener;
}

// --

// Check if a quit event has been registered.


// Update all listeners based on the current poll.
void TW_InputHandler_UpdateListeners()
{
    while( TW_InputHandler_Poll() == true )
    {
        for( int index = 0; index < inputHandler->size; index++ )
        {
            TW_Listener_Check( inputHandler->listeners[ index ]->type, inputHandler->listeners[ index ], inputHandler->events );
        }
    }
}


// Clear all listeners such that they have registered no events. Should be done at the end of every game loop.
void TW_InputHandler_ClearListeners()
{
    for( int index = 0; index < inputHandler->size; index++ )
    {
        TW_Listener_Clear( inputHandler->listeners[ index ] );
    }
}


bool TW_InputHandler_CheckQuit()
{
    TW_Listener* listener = TW_InputHandler_GetListenerType( TW_L_QUIT );
    if( listener != NULL )
    {
        return listener->quit->eventExists;
    }
    return false;
}


// Check if a key-down event was registered for the specified key. A listener must exist for this key.
bool TW_InputHandler_CheckKeyDown( SDL_Keycode key )
{
    for( int index = 0; index < inputHandler->size; index++ )
    {
        if( inputHandler->listeners[ index ]->type == TW_L_KEYDOWN )
        {
            if( inputHandler->listeners[ index ]->keyDown->key == key )
            {
                return inputHandler->listeners[ index ]->keyDown->eventExists;
            }
        }
    }
    return false;
}


// Check if a key-up event was registered for the specified key. A listener must exist for this key.
bool TW_InputHandler_CheckKeyUp( SDL_Keycode key )
{
    for( int index = 0; index < inputHandler->size; index++ )
    {
        if( inputHandler->listeners[ index ]->type == TW_L_KEYUP )
        {
            if( inputHandler->listeners[ index ]->keyUp->key == key )
            {
                return inputHandler->listeners[ index ]->keyUp->eventExists;
            }
        }
    }
    return false;
}


bool TW_InputHandler_CheckMouseMove()
{
    TW_Listener* listener = TW_InputHandler_GetListenerType( TW_L_MOUSEMOVE );
    if( listener != NULL )
    {
        return listener->mouseMove->eventExists;
    }
    return false;
}