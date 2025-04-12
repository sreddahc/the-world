#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"


// Type definitions

/**
 * TW_Texture - A wrapper object that contains all information relating to a texture.
 * 
 * Elements:
 * - SDL_Texture*   - texture           - SDL_Texture object, rendered image is stored here
 * - int            - textureWidth      - Width of the texture
 * - int            - textureHeight     - Height of the texture
 * - int            - x                 - x position where the texture will be rendered
 * - int            - y                 - y position where the texture will be rendered
 * - int            - renderWidth       - Width of the the render
 * - int            - renderHeight      - Height of the the render
 * - double         - angle             - Rotation of the texture
 * - SDL_RenderFlip - flip              - Flip the texture
 * - SDL_Rect*      - crop              - portion of the texture to render
 */
typedef struct TW_Texture {
    SDL_Texture* texture;       // SDL_Texture object, rendered image is stored here
    int textureWidth;           // Width of the texture
    int textureHeight;          // Height of the texture
    int x;                      // X position of the texture
    int y;                      // Y position of the texture
    int renderWidth;            // Width of the render
    int renderHeight;           // Height of the render
    double angle;               // Angle of the texture to render
    bool useColourKey;          // true = colour key exists, false = no colour key
    SDL_Colour colourKey;       // the colour to use as the colour key
    SDL_RendererFlip flip;      // Flip the texture
    SDL_Rect crop;              // Crop image to SDL_Rect
} TW_Texture;


// Function definitionss

/**
 * TW_Texture_CreateTexture - Creates a TW_Texture
 * 
 * Returns:
 * - TW_Texture*        - An empty TW_Texture
 */
TW_Texture* TW_Texture_CreateTexture();


/**
 * TW_Texture_LoadSurface - Create a TW_Texture from an SDL_Surface object.
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture to load the surface into
 * - SDL_Surface*       - surface       - The SDL_Surface object to load into a TW_Texture
 * 
 * Returns:
 * - bool               - true if successful, false if not
 */
bool TW_Texture_LoadSurface( TW_Texture* self, SDL_Surface* surface );


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


/**
 * TW_Texture_Crop - Crop a given TW_Texture object to the specified dimensions.
 * 
 * Args:
 * - TW_Texture*        - self          - The TW_Texture object to crop
 * - int                - x             - X position where the crop starts
 * - int                - y             - Y position where the crop starts
 * - int                - w             - Width of the crop
 * - int                - h             - Height of thecrop
 */
void TW_Texture_Crop(TW_Texture* self, int x, int y, int w, int h );


/**
 * TW_Texture_SetColourKey - Sets the colour key of a TW_Texture object such that a given
 *                           colour will treated as transparent.
 * 
 * Args:
 * - TW_Texture*        - self          - Set the colour key of this texture
 * - int                - r             - The red component of the colour key
 * - int                - g             - The green component of the colour key
 * - int                - b             - The blue component of the colour key
 */
void TW_Texture_SetColourKey( TW_Texture* self, int r, int g, int b );


// /**
//  * TW_Texture_UnsetColourKey - Unsets the colour key of a TW_Texture object so that no
//  *                             colour is transparent.
//  * 
//  * Args:
//  * - TW_Texture*        - self          - Unset the colour key of this texture
//  */
// void TW_Texture_UnsetColourKey( TW_Texture* self );