#pragma once

#include <SDL2/SDL.h>
#include "../../engine/maths.h"


// Type definitions

typedef struct TW_Component TW_Component;


/**
 * TW_Transform - A transform object used to provide basic information about an entity
 * 
 * Elements:
 * - TW_Coord*          - position      - The position of the entity on the x plane
 * - TW_Coord*          - centre        - The centre point of the entity. NULL defaults to { 0, 0 }
 * - float              - angle         - The angle of the entity (in degrees)
 * - float              - scale         - The scale of  the entity
 */
typedef struct TW_Transform {
    TW_Vector2* position;               // The position of the entity on the x plane
    TW_Vector2* centre;                 // The centre point of the entity. NULL defaults to { 0, 0 }
    double angle;                       // The angle of the entity (in degrees)
    double scale;
    SDL_RendererFlip flip;
    TW_Component* parent;               // Parent component if it exists, otherwise `NULL`
} TW_Transform;


// Function definitions

/**
 * TW_Transform_Create - Creates a TW_Transform object with the specified values
 * 
 * Args:
 * - TW_Vector2*        - position      - The position of the entity on the x plane
 * - TW_Vector2*        - centre        - The centre point of the entity. NULL defaults to { 0, 0 }
 * - float              - angle         - The angle of the entity (in degrees)
 * - float              - scale         - The scale of  the entity
 */
TW_Transform* TW_Transform_Create( int x, int y, double angle, double scale );


/**
 * TW_Transform_SetPosition - Set the position of the transform.
 * 
 * Args:
 * - TW_Transform*      - self          - Set the position of this transform object
 * - int                - x             - The x position
 * - int                - y             - The y position
 */
void TW_Transform_SetPosition( TW_Transform* self, int x, int y );


/**
 * TW_Transform_Free - Frees the resources used by a TW_Transform object
 * 
 * Args:
 * - TW_Transform*      - self          - The TW_Transform object to free
 */
void TW_Transform_Free( TW_Transform* self );
