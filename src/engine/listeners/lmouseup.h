#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>


// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * TW_L_MouseMove - Mouse-up listener object.
 * 
 * Elements:
 * - bool               - eventExists           - `true` if listener object recorded events, `false` otherwise
 */
typedef struct TW_L_MouseUp {
    bool eventExists;
} TW_L_MouseUp;


// Function definitions

/**
 * TW_L_MouseUp_Create - Creates a listener object that checks for mouse-up events.
 * 
 * Returns:
 * - TW_L_MouseUp*    - The mouse-up listener
 */
TW_L_MouseUp* TW_L_MouseUp_Create();


/**
 * TW_L_MouseUp_Free - Frees the resources used by a mouse-up listener object.
 * 
 * Args:
 * - TW_L_MouseUp*    - self              - The mouse-up listener to free
 */
void TW_L_MouseUp_Free( TW_L_MouseUp* self );


/**
 * TW_L_MouseUp_Check - If a mouse-up event has been registered - update the listener object.
 * 
 * Args:
 * - TW_L_MouseUp*    - self              - The mouse-up listener object to check
 * - SDL_Event          - event             - The event to check against
 */
void TW_L_MouseUp_Check( TW_L_MouseUp* self, SDL_Event event );


/**
 * TW_L_MouseUp_Clear - Clear the mouse-up listener object so no events are registered.
 * 
 * Args:
 * - TW_L_MouseUp*    - self              - The mouse-up listener to clear
 */
void TW_L_MouseUp_Clear( TW_L_MouseUp* self );
