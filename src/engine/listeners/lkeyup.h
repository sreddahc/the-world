#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * TW_L_KeyUp - Listen for a specific key being pressed.
 */
typedef struct TW_L_KeyUp {
    bool event;
    SDL_Keycode key;
} TW_L_KeyUp;


// Function definitions

/**
 * TW_L_KeyUp_Create - Create a key-up listener object.
 * 
 * Args:
 * - SDL_KeyCode        - key           - The key to monitor for a key-up event
 * 
 * Returns:
 * - TW_L_KeyUp*      - The key-up listener object
 */
TW_L_KeyUp* TW_L_KeyUp_Create( SDL_KeyCode key );


/**
 * TW_L_KeyUp_Free - Frees the resources used by a key-up listener object.
 * 
 * Args:
 * - TW_L_KeyUp*      - self          - The key-up listener object to free
 */
void TW_L_KeyUp_Free( TW_L_KeyUp* self );


/**
 * TW_L_KeyUp_Check - Check to see if a key-up event has been registered for the key
 *                      in this key-up listener object.
 * 
 * Args:
 * - TW_L_KeyUp*      - self          - The key-up listener object to check
 * - SDL_Event          - event         - The event to check against
 */
void TW_L_KeyUp_Check( TW_L_KeyUp* self, SDL_Event event );


/**
 * TW_L_KeyUp_Clear - Clears the key-up listener object so no events are registered.
 * 
 * Args:
 * - TW_L_KeyUp*      - self          - The key-up listener object to clear
 */
void TW_L_KeyUp_Clear( TW_L_KeyUp* self );