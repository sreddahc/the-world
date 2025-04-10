#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "renderer.h"


// Type definitions

/**
 * TW_Texture - A wrapper object that contains all information relating to a texture.
 * 
 * Elements:
 * - SDL_Texture*   - texture           - SDL_Texture object, rendered image is stored here
 * - int            - width             - Width of the texture
 * - int            - height            - Height of the texture
 */
typedef struct TW_Texture {
    SDL_Texture* texture;       // SDL_Texture object, rendered image is stored here
    int width;                  // Width of the texture
    int height;                 // Height of the texture
    double angle;               // Angle of the texture
    SDL_Rect* crop;             // Crop image to SDL_Rect
} TW_Texture;


// Function definitions

/**
 * TW_Texture_CreateTexture - Creates a TW_Texture
 * 
 * Returns:
 * - TW_Texture*        - An empty TW_Texture
 */
TW_Texture* TW_Texture_CreateTexture();

/**
 * TW_Texture_LoadImage - Renders a image at a given path into a TW_Texture object.
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture object
 * - char*              - path          - Path to the image to be rendered
 * 
 * Returns:
 * - bool               - true if successful, false if not
 */
bool TW_Texture_LoadImage( TW_Texture* self, char* path );

/**
 * TW_Texture_Render - Render a TW_Texture object.
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture object to render
 */
void TW_Texture_Render( TW_Texture* self );

/**
 * TW_Texture_Free - Free resources used by a TW_Texture object.
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture object
 */
void TW_Texture_Free( TW_Texture* self );
