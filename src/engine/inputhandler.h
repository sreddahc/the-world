#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>


// Type definitions

typedef struct TW_InputHandler {
    int eventsExist;
    SDL_Event events;
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


void TW_InputHandler_Free();