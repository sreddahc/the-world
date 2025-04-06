#pragma once

#include <stdbool.h>
#include "renderer.h"

// Type definitions

/**
 * TW_Animation - An animated texture.
 * 
 * Elements:
 * TW_Texture       - textureReel       - Texture with all animation components
 * int              - height            - Height of the animation texture
 * int              - width             - Width of the animation texture
 * int              - frameCount        - Number of frames in the animation
 * int              - currentFrame      - Current frame of the animation
 * TW_Texture       - texture           - Current frame rendered as a texture            
 */
typedef struct TW_Animation {
    int height;
    int width;
    int frameCount;
    int currentFrame;
    SDL_Rect* grid;
    TW_Texture texture;
} TW_Animation;


// Function definitions

/**
 * TW_Animation_Init - Initialises a TW_Animation object.
 * 
 * Args:
 * TW_Animation*    - self              - The TW_Animation object to initialise
 * char*            - path              - Path of the textureReel
 * int              - height            - The height of the animation
 * int              - width             - The width of the animation
 * int              - frameCount        - The number of frames in the animation
 */
bool TW_Animation_Init( TW_Animation* self, SDL_Renderer* renderer, char* path, int height, int width, int frameCount );


/**
 * TW_Animation_GetNextFrame - Gets the next frame texture in the animation and
 * increments the current frame counter.
 * 
 * Args:
 * TW_Animation*    - self              - The TW_Animation object
 * 
 * Returns:
 * bool             - true if no error, false otherwise
 */
void TW_Animation_GetNextFrame( TW_Animation* self );


/**
 * TW_Animation_Free - Frees resources used by a TW_Animation object.
 * 
 * Args:
 * TW_Animation*    - self              - The TW_Animation object
 */
void TW_Animation_Free( TW_Animation* self );