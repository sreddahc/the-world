#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>


// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * \brief Mouse-down listener object.
 * 
 * \param eventExists `bool` – `true` if listener recorded an event, `false` otherwise
 * \param button `Uint8` – The button on the mosue to listen for
 */
typedef struct TW_L_MouseDown {
    bool eventExists;
    Uint8 button;
} TW_L_MouseDown;


// Function definitions

/**
 * \brief Creates a listener that checks mouse-up events for a button.
 * 
 * \param button `Uint8` – Check for mouse-down events on this button.
 * 
 * \returns `TW_L_MouseDown*` – The mouse-down listener
 */
TW_L_MouseDown* TW_L_MouseDown_Create( Uint8 button );


/**
 * \brief Frees the resources used by a mouse-down listener object.
 * 
 * \param self `TW_L_MouseDown*` – The mouse-down listener to free
 */
void TW_L_MouseDown_Free( TW_L_MouseDown* self );


/**
 * \brief If a mouse-down event has been registered - update the listener object.
 * 
 * \param self `TW_L_MouseDown*` – The mouse-down listener object to check
 * \param event `SDL_Event` – The event to check against
 */
void TW_L_MouseDown_Check( TW_L_MouseDown* self, SDL_Event event );


/**
 * \brief Clear the mouse-down listener object so no events are registered.
 * 
 * \param self `TW_L_MouseDown*` – The mouse-down listener to clear
 */
void TW_L_MouseDown_Clear( TW_L_MouseDown* self );
