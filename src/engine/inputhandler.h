#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "listener.h"


// Type definitions

typedef struct TW_InputHandler {
    int eventsExist;
    SDL_Event events;
    int size;
    TW_Listener** listeners;
} TW_InputHandler;


// Function definitions

void TW_InputHandler_Create();


bool TW_InputHandler_Poll();


bool TW_InputHandler_CheckEvents();


bool TW_InputHandler_CheckKeyDown();


bool TW_InputHandler_CheckKeyPressed( SDL_Keycode key );


bool TW_InputHandler_CheckKeyDepressed( SDL_Keycode key );


bool TW_InputHandler_CheckMouse();


bool TW_InputHandler_CheckMouseMoved();


bool TW_InputHandler_CheckMousePressed();


bool TW_InputHandler_CheckMouseDepressed();


bool TW_InputHandler_CheckQuit();


/**
 * TW_InputHandler_Free - Free the resources used by the InputHandler.
 */
void TW_InputHandler_Free();


/**
 * TW_InputHandler_AddListener - Add a listener to the input handler.
 * 
 * Args:
 * - TW_Listener*           - listener      - The listener to add to the input handler
 */
void TW_InputHandler_AddListener( TW_Listener* listener );