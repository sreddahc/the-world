#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * TW_L_Quit - Quit listener object.
 * 
 * Elements:
 * - bool               - eventExists       - Quit event been registered? `true` if so, otherwise `false`
 */
typedef struct TW_L_Quit {
    bool eventExists;
} TW_L_Quit;


// Function definitions

/**
 * TW_L_Quit_Create - Creates a listener object that checks for quit events.
 * 
 * Returns:
 * - TW_L_Quit*         - The quit listener
 */
TW_L_Quit* TW_L_Quit_Create();


/**
 * TW_L_Quit_Free - Frees the resources used by a quit listener object.
 * 
 * Args:
 * - TW_L_Quit*         - self          - The quit listener object to free
 */
void TW_L_Quit_Free( TW_L_Quit* self );


/**
 * TW_L_Quit_Check - If a quit event has been registered - update the listener object.
 * 
 * Args:
 * - TW_L_Quit*         - self          - The quit listener object to check
 * - SDL_Event          - event         - The event to check against
 */
void TW_L_Quit_Check( TW_L_Quit* self, SDL_Event event );


/**
 * TW_L_Quit_Clear - Clears the quit listener object so no events are registered.
 * 
 * Args:
 * - TW_L_Quit*         - self          - The quit listener object to clear
 */
void TW_L_Quit_Clear( TW_L_Quit* self );
