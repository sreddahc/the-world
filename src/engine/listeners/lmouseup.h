#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>


// Type definitions

typedef struct TW_Listener TW_Listener;


/**
 * \brief Mouse-up listener object.
 * 
 * \param eventExists `bool` – `true` listener observes an event, otherwise `false`
 * \param button `Uint8` – The button to listen for
 */
typedef struct TW_L_MouseUp {
    bool eventExists;
    Uint8 button;
} TW_L_MouseUp;


// Function definitions

/**
 * \brief Creates a listener that checks mouse-up events for a button.
 * 
 * \param button `Uint8` – The button to create a listener event for
 * 
 * \returns `TW_L_MouseUp*` – The mouse-up listener
 */
TW_L_MouseUp* TW_L_MouseUp_Create( Uint8 button );


/**
 * \brief Frees the resources used by a mouse-up listener object.
 * 
 * \param self `TW_L_MouseUp*` – The mouse-up listener to free
 */
void TW_L_MouseUp_Free( TW_L_MouseUp* self );


/**
 * \brief If a mouse-up event has been registered - update the listener object.
 * 
 * \param self `TW_L_MouseUp*` – The mouse-up listener object to check
 * \param event `SDL_Event` – The event to check against
 */
void TW_L_MouseUp_Check( TW_L_MouseUp* self, SDL_Event event );


/**
 * \brief Clear the mouse-up listener object so no events are registered.
 * 
 * \param self `TW_L_MouseUp*` – The mouse-up listener to clear
 */
void TW_L_MouseUp_Clear( TW_L_MouseUp* self );
