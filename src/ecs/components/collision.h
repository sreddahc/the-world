#pragma once

#include "../../engine/maths.h"


// Type definitions

typedef struct TW_Component TW_Component;
typedef struct TW_Transform TW_Transform;


/**
 * TW_Collision - A bounding box used for identifying when entities collide.
 * 
 * Elements:
 * - TW_Vector2*        - position          - Position relative to parent entity transform
 * - TW_Vector2*        - size              - Size of the collision box
 * - TW_Component*      - parent            - Parent component object if exists, otherwise `NULL`
 */
typedef struct TW_Collision {
    TW_Vector2* position;                   // Position relative to parent entity transform
    TW_Vector2* size;                       // Size of the collision box
    TW_Component* parent;                   // Parent component object if exists, otherwise `NULL`
} TW_Collision;


// Function definitions

/**
 * TW_Collision_Create - Create a collision object based on provided parameters.
 * 
 * Args:
 * - int                - x                 - X position of collision object
 * - int                - y                 - Y position of collision object
 * - int                - w                 - Width of collision object
 * - int                - h                 - Height of collision object
 *
 * Returns:
 * - TW_Collision*      - Collision object
 */
TW_Collision* TW_Collision_Create( int x, int y, int w, int h );


/**
 * 
 */
void TW_Collision_GetRelativePosition();


/**
 * This is temporary... I have to think about how I want collisions to function.
 * I should also consider whether I want a move function that moves everything at once.
 */
void TW_Collision_Check( TW_Collision* self, TW_Transform* transform );


/**
 * TW_Collision_Free - Frees the resources used by a collision object.
 * 
 * Args:
 * - TW_Collision*      - self              - Collision object to free
 */
void TW_Collision_Free( TW_Collision* self );
