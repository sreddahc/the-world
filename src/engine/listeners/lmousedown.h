#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>


// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * TW_L_MouseMove - Mouse-down listener object.
 * 
 * Elements:
 * - bool               - eventExists           - `true` if listener object recorded events, `false` otherwise
 */
typedef struct TW_L_MouseDown {
    bool eventExists;
} TW_L_MouseDown;


// Function definitions

/**
 * TW_L_MouseDown_Create - Creates a listener object that checks for mouse-down events.
 * 
 * Returns:
 * - TW_L_MouseDown*    - The mouse-down listener
 */
TW_L_MouseDown* TW_L_MouseDown_Create();


/**
 * TW_L_MouseDown_Free - Frees the resources used by a mouse-down listener object.
 * 
 * Args:
 * - TW_L_MouseDown*    - self              - The mouse-down listener to free
 */
void TW_L_MouseDown_Free( TW_L_MouseDown* self );


/**
 * TW_L_MouseDown_Check - If a mouse-down event has been registered - update the listener object.
 * 
 * Args:
 * - TW_L_MouseDown*    - self              - The mouse-down listener object to check
 * - SDL_Event          - event             - The event to check against
 */
void TW_L_MouseDown_Check( TW_L_MouseDown* self, SDL_Event event );


/**
 * TW_L_MouseDown_Clear - Clear the mouse-down listener object so no events are registered.
 * 
 * Args:
 * - TW_L_MouseDown*    - self              - The mouse-down listener to clear
 */
void TW_L_MouseDown_Clear( TW_L_MouseDown* self );
