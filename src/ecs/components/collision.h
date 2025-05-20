#pragma once

#include <stdbool.h>
#include "../../engine/maths.h"


// Type definitions

typedef struct TW_Component TW_Component;
typedef struct TW_Entity TW_Entity;


/**
 * \brief A bounding box used for identifying when entities collide.
 *        
 *        If a TW_Collision is `solid`, when a scene is run, an attempt to resolve the
 *        physics aspect of the collision is attempted. If `immovable` then the physics
 *        will not affect this objects position.
 * 
 * \param position (TW_Vector2*) Position relative to parent entity transform
 * \param centre (TW_Vector2*) Centre of the collision object, Default: `{ 0, 0 }`
 * \param size (TW_Vector2*) Size of the collision box
 * \param oldPosition (TW_Vector2*) Old position of the transform prior to moving
 * \param parent (TW_Component*) Parent component object if exists, otherwise `NULL`
 * \param solid (bool) Is this collision box solid? `true` if so, `false` otherwise
 * \param immovable (bool) Is this collision box immovable? `true` if so, `false` otherwise
 * \param collisionSize (int) Number of entities that have been collided with
 * \param collisionMax (int) Size of the collisions pointer array
 * \param collisions (TW_Entity**) array of pointers which point to the entities that have been collided with
 */
typedef struct TW_Collision {
    TW_Vector2* position;                   // Position relative to parent entity transform
    TW_Vector2* centre;                     // Centre of the collision object, Default: `{ 0, 0 }`
    TW_Vector2* size;                       // Size of the collision box
    TW_Component* parent;                   // Parent component object if exists, otherwise `NULL`
    bool hasPhysics;                        // Is this collision box solid? `true` if so, `false` otherwise
    bool fixed;                             // Is the object immovable by force?
    TW_Vector2* oldPosition;                // Old position of the transform prior to moving
    int collisionSize;                     // Number of entities that have been collided with
    int collisionMax;                       // Size of collisions pointer array (required for cleanup)
    TW_Entity** collisions;                 // array of pointers which point to entities that have been collided with
} TW_Collision;


// Function definitions

/**
 * \brief Create a collision object based on provided parameters.
 * 
 * \param x (int) X position of collision object relative to the entity transf orm
 * \param y (int) Y position of collision object relative to the entity transform
 * \param w (int) Width of collision object
 * \param h (int) Height of collision object
 *
 * \returns (TW_Collision*) Collision object
 */
TW_Collision* TW_Collision_Create( int x, int y, int w, int h );


/**
 * \brief Frees the resources used by a collision object.
 * 
 * \param self (TW_Collision*) Collision object to free
 */
void TW_Collision_Free( TW_Collision* self );


/**
 * \brief Get current position relative to target entity
 * 
 * \param self (TW_Collision*) Current collision object
 * \param target (TW_Entity*) Target entity to get relative position of
 */
void TW_Collision_GetAbsolutePosition( TW_Collision* self, TW_Entity* target );


/**
 * \brief Test whether current entity collides with a target entity
 * 
 * \param self (TW_Collision*) Current collision object
 * \param target (TW_Entity*) Target entity to test collision against
 * 
 * \returns (bool) `true` if collision detected, otherwise `false`
 */
bool TW_Collision_Check( TW_Entity* self, TW_Entity* target );


/**
 * \brief Run the collision object. This should be done every game loop as long as the
 *        game is not paused.
 * 
 * \param self (TW_Collision*) The collision object to run
 */
void TW_Collision_Run( TW_Collision* self );


/**
 * \brief Add a references to collision objects where a collision has been observed.
 * 
 * \param self (TW_Collision*) Entities to this collision object
 * \param target (TW_Entity*) The entities to add
 */
void TW_Collision_AddCollisions( TW_Collision* self, TW_Entity* target );


/**
 * \brief Clear all references to collisions.
 * 
 * \param self (TW_Collision*) Clear references to collisions from this collision object
 */
void TW_Collision_ClearCollisions( TW_Collision* self );


/**
 * \brief Attempt to resolve the physics of 2 entities which have physics.
 * 
 * \param eA `TW_Entity*` – Entity A
 * \param eB `TW_Entity*` – Entity B
 */
void TW_Collision_Resolve( TW_Entity* eA, TW_Entity* eB );
