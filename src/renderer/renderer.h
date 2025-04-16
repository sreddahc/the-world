#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "texture.h"


// Type definitions

/**
 * TW_CreateRenderer - Create the renderer
 * 
 * Args:
 * - SDL_Window*    - window        - The window where rendering is displayed
 * - int            - index         - The index of the rendering driver to initialise, or -1
 *                                    to initialise the first one supporting the requested flags
 * - Uint32         - flags         - 0, or one or more SDL_RendererFlags OR'd together
 */
void TW_CreateRenderer( SDL_Window* window, int index, Uint32 flags);


/**
 * TW_GetRenderer - Get the renderer
 * 
 * Returns:
 * - SDL_Renderer*  - The renderer
 */
SDL_Renderer* TW_GetRenderer();


/**
 *  TW_DestroyRenderer - Destroy the renderer
 */
void TW_DestroyRenderer();
