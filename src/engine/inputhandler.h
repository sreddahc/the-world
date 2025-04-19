#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>


// Type definitions

typedef struct TW_InputHandler {
    int eventsExist;
    SDL_Event events;
} TW_InputHandler;


// Function definitions


TW_InputHandler* TW_InputHandler_Create();


void TW_InputHandler_Poll();


bool TW_InputHandler_CheckEvents();


bool TW_InputHandler_CheckKeyboard();


bool TW_InputHandler_CheckKeyPressed( SDL_Keycode key );


bool TW_InputHandler_CheckQuit();


void TW_InputHandler_Free();