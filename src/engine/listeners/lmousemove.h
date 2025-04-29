#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>


// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * TW_L_MouseMove - Mouse-move listener object.
 * 
 * Elements:
 * - bool               - eventExists           - `true` if listener object recorded events, `false` otherwise
 */
typedef struct TW_L_MouseMove {
    bool eventExists;
} TW_L_MouseMove;


// Function definitions

/**
 * TW_L_MouseMove_Create - Creates a listener object that checks for mouse-move events.
 * 
 * Returns:
 * - TW_L_MouseMove*    - The mouse-move listener
 */
TW_L_MouseMove* TW_L_MouseMove_Create();


/**
 * TW_L_MouseMove_Free - Frees the resources used by a mouse-move listener object.
 * 
 * Args:
 * - TW_L_MouseMove*    - self              - The mouse-move listener to free
 */
void TW_L_MouseMove_Free( TW_L_MouseMove* self );


/**
 * TW_L_MouseMove_Check - If a mouse-move event has been registered - update the listener object.
 * 
 * Args:
 * - TW_L_MouseMove*    - self              - The mouse-move listener object to check
 * - SDL_Event          - event             - The event to check against
 */
void TW_L_MouseMove_Check( TW_L_MouseMove* self, SDL_Event event );


/**
 * TW_L_MouseMove_Clear - Clear the mouse-move listener object so no events are registered.
 * 
 * Args:
 * - TW_L_MouseMove*    - self              - The mouse-move listener to clear
 */
void TW_L_MouseMove_Clear( TW_L_MouseMove* self );
