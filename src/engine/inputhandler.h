#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "listener.h"


// Type definitions

typedef struct TW_InputHandler {
    int eventsExist;
    SDL_Event events;
    int size;
    TW_Listener** listeners;
} TW_InputHandler;


// Function definitions

/**
 * TW_InputHandler_Create - Create the input handler. There is one in the game. No inputs
 *                          are processed if it is not created.
 */
void TW_InputHandler_Create();


/**
 * TW_InputHandler_Free - Free the resources used by the InputHandler.
 */
void TW_InputHandler_Free();


/**
 * TW_InputHandler_Poll - Poll for an event.
 * 
 * Returns:
 * - bool                   - `true` if there are events, `false` otherwise.
 */
bool TW_InputHandler_Poll();


/**
 * TW_InputHandler_CheckEvents - Check if there are events to process.
 * 
 * Returns:
 * - bool                   - `true` if there are events, `false` otherwise.
 */
bool TW_InputHandler_CheckEvents();


/**
 * TW_InputHandler_AddListener - Add a listener to the input handler.
 * 
 * Args:
 * - TW_Listener*           - listener      - The listener to add to the input handler
 */
void TW_InputHandler_AddListener( TW_Listener* listener );


/**
 * TW_InputHandler_GetListenerType - Retrieve a listener of the specified type.
 * 
 * Args:
 * - enum TW_ListenerType   - type          - The type of listener to find
 * 
 * Returns:
 * - TW_Listener*           - The listener requested (or `NULL` if not found)
 */
TW_Listener* TW_InputHandler_GetListenerType( enum TW_ListenerType type );


/**
 * TW_InputHandler_UpdateListeners - Update all listeners based on the current poll.
 *                                   Should be done at the beginning of every game loop.
 */
void TW_InputHandler_UpdateListeners();


/**
 * TW_InputHandler_ClearListeners - Clear all listeners such that they have registered no
 *                                  events. Should be done at the end of every game loop.
 */
void TW_InputHandler_ClearListeners();


/**
 * TW_InputHandler_CheckKeyDown - Check if a key-down event was registered for the
 *                                specified key. A listener must exist for this key.
 * 
 * Args:
 * - SDL_Keycode            - key           - The key to check
 * 
 * Returns:
 * - bool                   - `true` if key-down event was registered, `false` otherwise
 */
bool TW_InputHandler_CheckKeyDown( SDL_Keycode key );


/**
 * TW_InputHandler_CheckKeyUp - Check if a key-up event was registered for the specified
 *                              key. A listener must exist for this key.
 * 
 * Args:
 * - SDL_Keycode            - key           - The key to check
 * 
 * Returns:
 * - bool                   - `true` if key-up event was registered, `false` otherwise
 */
bool TW_InputHandler_CheckKeyUp( SDL_Keycode key );



/**
 * TW_InputHandler_CheckMouseDown - Check if a mouse-down event was registered.
 * 
 * Returns:
 * - bool                   - `true` if mouse-down event was registered, `false` otherwise
 */
bool TW_InputHandler_CheckMouseDown();


/**
 * TW_InputHandler_CheckMouseMove - Check if a mouse-move event was registered.
 * 
 * Returns:
 * - bool                   - `true` if mouse-move event was registered, `false` otherwise
 */
bool TW_InputHandler_CheckMouseMove();


/**
 * TW_InputHandler_CheckMouseDown - Check if a mouse-down event was registered.
 * 
 * Returns:
 * - bool                   - `true` if mouse-down event was registered, `false` otherwise
 */
bool TW_InputHandler_CheckMouseUp();


/**
 * TW_InputHandler_CheckQuit - Check if a quit event has been registered.
 * 
 * Returns:
 * - bool               - `true` if quit event registered, otherwise `false`
 */
bool TW_InputHandler_CheckQuit();