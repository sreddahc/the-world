#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Type definitions

enum TW_ListenerType
{
    TW_L_QUIT,
    TW_L_KEYDOWN,
    TW_L_KEYUP,
    TW_L_MOUSEDOWN,
    TW_L_MOUSEUP,
    TW_L_MOUSEMOVE,
    TW_L_TOTAL
};


/**
 * TW_Listener - A listener object that listens for events
 */
typedef struct TW_Listener {
    enum TW_ListenerType type;
    bool event;
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
 * - TW_Listener*       - self          - Free the resources used by this listener
 */
void TW_Listener_Free( TW_Listener* self );