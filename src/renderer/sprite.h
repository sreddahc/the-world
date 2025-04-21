#pragma once

#include "texture.h"


// Type definitions

typedef struct TW_Component TW_Component;


/**
 * TW_Sprite - A sprite based off a sprite sheet
 * 
 * Elements:
 * - TW_Texture*    - texture           - The texture that will be used by the sprite
 * - int            - width             - Width of the sprite
 * - int            - height            - Height of the sprite
 * - SDL_Rect*      - grid              - Texture grid based on the height and width of the sprite
 * - int            - gridSize          - Number of grids/subdivisions of the parent texture
 * - int            - currentSprite     - The sprite to display
 */
typedef struct TW_Sprite {
    TW_Texture* texture;    // The texture that will be used by the sprite
    int width;              // Width of the sprite
    int height;             // Height of the sprite
    SDL_Rect* grid;         // Texture grid based on the height and width of the sprite
    int gridSize;           // Number of grids/subdivisions of the parent texture
    int currentSprite;      // The sprite to display
    TW_Component* parent;   // Parent component if it exists, otherwise `NULL`
} TW_Sprite;

// Function definitions


/**
 * TW_Sprite_Create - Create a sprite from a sprite sheet from a given path
 * 
 * Args:
 * - char*          - path          - The path to the sprite sheet
 * - int            - width         - The width of the sprite
 * - int            - height        - The height of the sprite
 */
TW_Sprite* TW_Sprite_Create( char* path, int width, int height );


/**
 * TW_Sprite_Free - Free the resources used by a sprite object
 * 
 * Args:
 * - TW_Sprite*     - self          - The TW_Sprite object to free
 */
void TW_Sprite_Free( TW_Sprite* self );


/**
 * TW_Sprite_Render - Render the current TW_Sprite object
 * Args:
 * - TW_Sprite*     - self          - The sprite sheet
 * - int            - sprite        - The frame from the sprite sheet to render
 */
void TW_Sprite_Render( TW_Sprite* self, TW_Transform* transform );