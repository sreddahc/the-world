#pragma once

#include "../renderer/renderer.h"


// Type definitions

/**
 * TW_Entity - A wrapper object that contains all information to do with a player sprite
 * 
 * Elements:
 * - TW_Texture*    - texture       - The texture of the sprite
 * - TW_Coord*      - position      - The position of an object on the screen
 */
typedef struct TW_Entity {
    TW_Texture texture;
    TW_Coord position;
} TW_Entity;


// Function definitions

/**
 * TW_Sprite_Init - Initialise a TW_Sprite object.
 * 
 * Args:
 * - TW_Sprite*     - self      - The TW_Sprite object to be initialised      
 */
void TW_Entity_Init( TW_Entity* self );


/**
 * TW_Entity_Load - 
 */
void TW_Entity_Load( TW_Entity* self, SDL_Renderer* renderer, char* spriteMap, int x, int y );