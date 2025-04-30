#pragma once

#include <stdbool.h>
#include "../../engine/maths.h"


// Type definitions

typedef struct TW_Component TW_Component;
typedef struct TW_Entity TW_Entity;


/**
 * TW_Collision - A bounding box used for identifying when entities collide.
 * 
 * Elements:
 * - TW_Vector2*        - position          - Position relative to parent entity transform
 * - TW_Vector2*        - centre            - Centre of the collision object, Default: `{ 0, 0 }`
 * - TW_Vector2*        - size              - Size of the collision box
 * - TW_Vector2*        - oldPosition       - Old position of the transform prior to moving
 * - TW_Component*      - parent            - Parent component object if exists, otherwise `NULL`
 * - bool               - solid             - Is this collision box solid? `true` if so, `false` otherwise
 */
typedef struct TW_Collision {
    TW_Vector2* position;                   // Position relative to parent entity transform
    TW_Vector2* centre;                     // Centre of the collision object, Default: `{ 0, 0 }`
    TW_Vector2* size;                       // Size of the collision box
    TW_Component* parent;                   // Parent component object if exists, otherwise `NULL`
    bool immovable;                         // Is the object immovable by force?
    bool solid;                             // Is this collision box solid? `true` if so, `false` otherwise
    TW_Vector2* oldPosition;                // Old position of the transform prior to moving
    int collisionCount;                     // Number of entities that have been collided with
    int collisionBufferSize;                // Size of collisions pointer array (required for cleanup)
    TW_Entity** collisions;                 // array of pointers which point to entities that have been collided with
} TW_Collision;


// Function definitions

/**
 * TW_Collision_Create - Create a collision object based on provided parameters.
 * 
 * Args:
 * - int                - x                 - X position of collision object relative to the entity transform
 * - int                - y                 - Y position of collision object relative to the entity transform
 * - int                - w                 - Width of collision object
 * - int                - h                 - Height of collision object
 *
 * Returns:
 * - TW_Collision*      - Collision object
 */
TW_Collision* TW_Collision_Create( int x, int y, int w, int h );


/**
 * TW_Collision_Free - Frees the resources used by a collision object.
 * 
 * Args:
 * - TW_Collision*      - self              - Collision object to free
 */
void TW_Collision_Free( TW_Collision* self );


/**
 * TW_Collision_GetAbsolutePosition - Get current position relative to target entity
 * 
 * Args:
 * - TW_Collision*      - self              - Current collision object
 * - TW_Entity*         - target            - Target entity to get relative position of
 */
void TW_Collision_GetAbsolutePosition( TW_Collision* self, TW_Entity* target );


/**
 * TW_Collision_Check - Test whether current entity collides with a target entity
 * 
 * Args:
 * - TW_Collision*      - self              - Current collision object
 * - TW_Entity*         - target            - Target entity to test collision against
 * 
 * Returns:
 * - bool               - `true` if collision detected, otherwise `false`
 */
bool TW_Collision_Check( TW_Entity* self, TW_Entity* target );


/**
 * TW_Collision_Run - Run the collision object. This should be done every game loop as
 *                    long as the game is not paused.
 */
void TW_Collision_Run( TW_Collision* self );


/**
 * TW_Collision_AddCollisions - Add a references to collision objects where a collision
 *                              has been observed.
 * 
 * Args:
 * - TW_Collision*      - self              - Entities to this collision object
 * - TW_Entity*         - target            - The entities to add
 */
void TW_Collision_AddCollisions( TW_Collision* self, TW_Entity* target );


/**
 * TW_Collision_ClearCollisions - Clear all references to collisions.
 */
void TW_Collision_ClearCollisions( TW_Collision* self );
