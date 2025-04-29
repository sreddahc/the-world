#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "listeners/lkeydown.h"
#include "listeners/lkeyup.h"
#include "listeners/lmousedown.h"
#include "listeners/lmousemove.h"
#include "listeners/lquit.h"

// Type definitions

enum TW_ListenerType
{
    TW_L_KEYDOWN,
    TW_L_KEYUP,
    TW_L_MOUSEDOWN,
    TW_L_MOUSEMOVE,
    TW_L_MOUSEUP,
    TW_L_QUIT,
    TW_L_TOTAL
};


/**
 * TW_Listener - A listener object that listens for events
 */
typedef struct TW_Listener {
    enum TW_ListenerType type;
    union {
        TW_L_KeyDown* keyDown;
        TW_L_KeyUp* keyUp;
        TW_L_MouseDown* mouseDown;
        TW_L_MouseMove* mouseMove;
        TW_L_Quit* quit;
    };
} TW_Listener;


// Function definitions

/**
 * TW_Listener_Create - Create a listener object to listen for events.
 * 
 * Returns:
 * - TW_Listener*       - Initialised listener object 
 */
TW_Listener* TW_Listener_Create();


/**
 * TW_Listener_Free - Free the resources used by a listener object.
 * 
 * Args:
 * - TW_Listener*           - self          - Free the resources used by this listener
 */
void TW_Listener_Free( TW_Listener* self );


/**
 * TW_Listener_Add - Add a listener of a given type.
 * 
 * Args:
 * - enum TW_ListenerType   - type          - The listener type to add
 * - void*                  - value         - The listener object to add
 */
TW_Listener* TW_Listener_Add( enum TW_ListenerType type, void* value );


/**
 * TW_Listener_Check - Check an SDL event against against a listener.
 * 
 * Args:
 * - enum TW_ListenerType   - type          - The listener type to check
 * - TW_Listener*           - value         - The listener to check the event against
 * - SDL_Event              - event         - The event to check
 */
void TW_Listener_Check( enum TW_ListenerType type, TW_Listener* listener, SDL_Event event );


/**
 * TW_Listener_Clear - Clear the state of a given listener such that it has no events.
 * 
 * Args:
 * - TW_Listener*           - value         - The listener to clear
 */
void TW_Listener_Clear( TW_Listener* self );
