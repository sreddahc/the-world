#include "inputhandler.h"


static TW_InputHandler* inputHandler = NULL;


TW_InputHandler* TW_InputHandler_Create()
{
    inputHandler = malloc( sizeof( TW_InputHandler ) );
    inputHandler->eventsExist = 0;
}

void TW_InputHandler_Poll()
{
    inputHandler->eventsExist = SDL_PollEvent( &inputHandler->events );
}


bool TW_InputHandler_CheckEvents()
{
    if( inputHandler->eventsExist != 0 )
    {
        return true;
    }
    return false;
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


bool TW_InputHandler_CheckKeyboard()
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
    if( TW_InputHandler_CheckKeyboard() == true )
    {
        if( inputHandler->events.key.keysym.sym == key )
        {
            return true;
        }
    }
    return false;
}


void TW_InputHandler_Free()
{
    inputHandler->eventsExist = 0;
    free( inputHandler );
}
