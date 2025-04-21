#include "inputhandler.h"


static TW_InputHandler* inputHandler = NULL;


TW_InputHandler* TW_InputHandler_Create()
{
    inputHandler = malloc( sizeof( TW_InputHandler ) );
    inputHandler->eventsExist = 0;
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


void TW_InputHandler_Free()
{
    inputHandler->eventsExist = 0;
    free( inputHandler );
}
