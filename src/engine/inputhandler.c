#include "inputhandler.h"


static TW_InputHandler* inputHandler = NULL;


void TW_InputHandler_Create()
{
    inputHandler = malloc( sizeof( TW_InputHandler ) );
    inputHandler->eventsExist = 0;
    inputHandler->size = 0;
    inputHandler->listeners = NULL;
}


bool TW_InputHandler_CheckEvents()
{
    if( inputHandler->eventsExist != 0 )
    {
        return true;
    }
    return false;
}


bool TW_InputHandler_Poll()
{
    inputHandler->eventsExist = SDL_PollEvent( &inputHandler->events );
    return TW_InputHandler_CheckEvents();
}


bool TW_InputHandler_CheckQuit()
{
    if( TW_InputHandler_CheckEvents() == true )
    {
        if( inputHandler->events.type == SDL_QUIT )
        {
            return true;
        }
    }
    return false;
}


bool TW_InputHandler_CheckKeyDown()
{
    if( TW_InputHandler_CheckEvents() == true )
    {
        if( inputHandler->events.type == SDL_KEYDOWN )
        {
            return true;
        }
    }
    return false;
}


bool TW_InputHandler_CheckKeyPressed( SDL_Keycode key )
{
    if( TW_InputHandler_CheckEvents() == true )
    {
        if( inputHandler->events.type == SDL_KEYDOWN && inputHandler->events.key.repeat == 0 )
            {
            if( inputHandler->events.key.keysym.sym == key )
            {
                return true;
            }
        }
    }
    return false;
}


bool TW_InputHandler_CheckKeyDepressed( SDL_Keycode key )
{
    if( TW_InputHandler_CheckEvents() == true )
    {
        if( inputHandler->events.type == SDL_KEYUP && inputHandler->events.key.repeat == 0 )
            {
            if( inputHandler->events.key.keysym.sym == key )
            {
                return true;
            }
        }
    }
    return false;
}


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


bool TW_InputHandler_CheckMouseMoved()
{
    if( TW_InputHandler_CheckMouse() == true )
    {
        if( inputHandler->events.type == SDL_MOUSEMOTION )
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


bool TW_InputHandler_L_CheckQuit()
{
    TW_Listener* quitListener = TW_InputHandler_GetListenerType( TW_L_QUIT );
    // if( quitListener != NULL )
    // {
        if( quitListener->event == true )
        {
            printf( "!!!\n" );
            return quitListener->quit->quit;
        }
    // }
    return false;
}


// Update all listeners based on the current poll.
void TW_InputHandler_UpdateListeners()
{
    // printf("> %d\n", inputHandler->size);
    // Poll for events
    while( TW_InputHandler_Poll() == true )
    {
        for( int index = 0; index < inputHandler->size; index++ )
        {
            TW_Listener_Check( inputHandler->listeners[ index ]->type, inputHandler->listeners[ index ], inputHandler->events );
        }
    }
}


void TW_InputHandler_ClearListeners()
{
    for( int index = 0; index < inputHandler->size; index++ )
    {
        switch ( inputHandler->listeners[ index ]->type )
        {
        case TW_L_QUIT:
            TW_L_Quit_Clear( inputHandler->listeners[ index ]->quit );
            break;
        
        default:
            break;
        }
    }
}
