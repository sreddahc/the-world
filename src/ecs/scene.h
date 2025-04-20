#pragma once

#include "entity.h"


// Type definitions

/**
 * TW_Scene - Buffer of Entities
 * 
 * Elements:
 * - int            - size          - Size of the scene (Number of Entities in the scene)
 * - TW_Entity**    - entities      - The entities
 */
typedef struct TW_Scene {
    int size;
    TW_Entity** entities;
} TW_Scene;


// Function definitions

/**
 * TW_Scene_Create - Creates a scene to store entities in.
 * 
 * Returns:
 * TW_Scene*        - Returns an empty scene
 */
TW_Scene* TW_Scene_Create();


/**
 * TW_Scene_AddEntity - Creates a scene to store entities in.
 * 
 * Args:
 * - TW_Scene*      - self          - The scene to add entities to
 * - TW_Entity*     - entity        - The entity to add to a scene
 */
void TW_Scene_AddEntity( TW_Scene* self, TW_Entity* entity );


/**
 * TW_Scene_Free - Free the resources used by a scene.
 * 
 * Args:
 * - TW_Scene*      - self          - The scene to free
 */
void TW_Scene_Free( TW_Scene* self );


// --- DEVELOPER ZONE !! DANGER !! COMMENTS MAY NOT EXIST ---

// Developers note: This should probably be broken up...
/**
 * TW_Scene_Render - Given a scene, attempts to render all entities
 * 
 * Args:
 * - TW_Scene*      - self          - The scene to render
 */
void TW_Scene_Render( TW_Scene* self );


/**
 * TW_Scene_Run - Run logic components in scene entities.
 * 
 * Args:
 * - TW_Scene*      - self          - The scene to run logic components from
 */
void TW_Scene_Run( TW_Scene* self );