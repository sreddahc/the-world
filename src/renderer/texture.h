#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "renderer.h"


// Type definitions

typedef struct TW_Component TW_Component;


/**
 * TW_Colour - A Colour object
 * 
 * Elements:
 * - int            - r                 - Red
 * - int            - g                 - Green
 * - int            - b                 - Blue
 */
typedef struct TW_Colour{
    int r;          // Red
    int g;          // Green
    int b;          // Blue
    int a;          // Alpha
} TW_Colour;

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
    int renderWidth;            // Width of the render
    int renderHeight;           // Height of the render
    SDL_RendererFlip flip;      // Flip the texture
    SDL_Rect crop;              // Crop image to SDL_Rect
    TW_Component* parent;       // Parent component if it exists, otherwise `NULL`
} TW_Texture;


// Function definitions

/**
 * TW_Colour_Create - Create a colour object given a red, green and blue value
 * 
 * Args:
 * - int            - r             - Red
 * - int            - g             - Green
 * - int            - b             - Blue
 * 
 * Returns:
 * - TW_Colour*     - Returns a TW_Colour object
 */
TW_Colour* TW_Colour_Create( int r, int g, int b, int a );


/**
 * TW_Colour_Get - Get an SDL_Colour object from a TW_Colour object
 * 
 * Args:
 * - TW_Colour*     - self          - The TW_Colour object to obtain the SDL_Colour from
 * 
 * Returns:
 * - SDL_Colour     - Returns a SDL_Colour object
 */
SDL_Colour TW_Colour_Get( TW_Colour* self );


/**
 * TW_Colour_Free - Free the resources used by a TW_Colour object
 * 
 * Args:
 * - TW_Colour*     - self          - The TW_Colour object to free
 */
void TW_Colour_Free( TW_Colour* self );


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
 * - SDL_Rect           - region        - The part of the image to crop to
 */
void TW_Texture_Crop(TW_Texture* self, SDL_Rect region );
