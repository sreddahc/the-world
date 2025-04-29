#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * TW_L_KeyDown - Listen for a specific key being pressed.
 */
typedef struct TW_L_KeyDown {
    bool eventExists;
    SDL_Keycode key;
} TW_L_KeyDown;


// Function definitions

/**
 * TW_L_KeyDown_Create - Create a key-down listener object.
 * 
 * Args:
 * - SDL_KeyCode        - key           - The key to monitor for a key-down event
 * 
 * Returns:
 * - TW_L_Keydown*      - The key-down listener object
 */
TW_L_KeyDown* TW_L_KeyDown_Create( SDL_KeyCode key );


/**
 * TW_L_KeyDown_Free - Frees the resources used by a key-down listener object.
 * 
 * Args:
 * - TW_L_KeyDown*      - self          - The key-down listener object to free
 */
void TW_L_KeyDown_Free( TW_L_KeyDown* self );


/**
 * TW_L_KeyDown_Check - Check to see if a key-down event has been registered for the key
 *                      in this key-down listener object.
 * 
 * Args:
 * - TW_L_KeyDown*      - self          - The key-down listener object to check
 * - SDL_Event          - event         - The event to check against
 */
void TW_L_KeyDown_Check( TW_L_KeyDown* self, SDL_Event event );


/**
 * TW_L_KeyDown_Clear - Clears the key-down listener object so no events are registered.
 * 
 * Args:
 * - TW_L_KeyDown*      - self          - The key-down listener object to clear
 */
void TW_L_KeyDown_Clear( TW_L_KeyDown* self );