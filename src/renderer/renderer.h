#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "texture.h"


// Type definitions

/**
 * TW_Coord - an vector of size 2 that provides the x and y coordinates of an object
 * 
 * Elements:
 * - int            - x                 - The x position of an object
 * - int            - y                 - The y position of an object
 */
typedef struct TW_Coord {
    int x;
    int y;
} TW_Coord;


void TW_CreateRenderer( SDL_Window* window, int index, Uint32 flags);

SDL_Renderer* TW_GetRenderer();

void TW_DestroyRenderer();


// Function definitions


/**
 * TW_Texture_SetBlendMode - Set the blend mode that will be used in blending operations.
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture object
 * - SDL_BlendMode      - blending      - The blend mode that will be set for blending operations
 */
// void TW_Texture_SetBlendMode( TW_Texture* self, SDL_BlendMode blending );


/**
 * TW_Texture_SetColour - Sets the colour of a texture.
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture object
 * - Uint8              - red           - Amount of Red to include in texture
 * - Uint8              - green         - Amount of Green to include in texture
 * - Uint8              - blue          - Amount of Blue to include in texture
 */
// void TW_Texture_SetColour( TW_Texture* self, Uint8 red, Uint8 green, Uint8 blue);


/**
 * TW_Texture_SetAlpha - Sets the transparancy of a texture
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture object
 * - Uint8              - alpha         - Alpha: 0 = fully transparent to 255 = completely opaque.
 */
// void TW_Texture_SetAlpha( TW_Texture* self, Uint8 alpha );
