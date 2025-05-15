#pragma once

#include "entity.h"


// Type definitions

/**
 * \brief Buffer of Entities
 * 
 * \param size `int` – Size of the scene (Number of Entities in the scene)
 * \param maxSize `int` – Maximum size of scene.
 * \param entities `TW_Entity**` – The entities
 */
typedef struct TW_Scene {
    int size;
    int maxSize;
    TW_Entity** entities;
} TW_Scene;


// Function definitions

/**
 * \brief Creates a scene to store entities in.
 * 
 * Returns:
 * \returns `TW_Scene*` – An empty scene
 */
TW_Scene* TW_Scene_Create();


/**
 * \brief Free the resources used by a scene.
 * 
 * \param self `TW_Scene*` – The scene to free
 */
void TW_Scene_Free( TW_Scene* self );


/**
 * \brief Creates a scene to store entities in.
 * 
 * \param self `TW_Scene*` – The scene to add entities to
 * \param entity `TW_Entity*` – The entity to add to a scene
 */
void TW_Scene_AddEntity( TW_Scene* self, TW_Entity* entity );


/**
 * \brief Remove an entity from a scene.
 * 
 * \param self `TW_Scene*` – The scene to remove the entity from
 * \param entity `TW_Entity*` - The entity to remove from the scene
 */
void TW_Scene_RemoveEntity( TW_Scene* self, TW_Entity* entity );

/**
 * \brief Run logic components in a scene.
 * 
 * \param self `TW_Scene*` – Run logic for entities in this scene
 */
void TW_Scene_RunLogic( TW_Scene* self );


/**
 * \brief Run physics engine on a scene.
 * 
 * \param self `TW_Scene*` – Run physics on entities in this scene.
 */
void TW_Scene_RunPhysics( TW_Scene* self );


/**
 * \brief Render all entities in a scene.
 * 
 * \param `TW_Scene*` – Render entities in this scene
 */
void TW_Scene_Render( TW_Scene* self );


/**
 * \brief Clear the state of all entities in a scene. Run at the end of every game loop.
 *        If an entity is marked for destruction, free the entity.
 * 
 * \param self `TW_Scene*` – Clear entities in this scene.
 */
void TW_Scene_Clear( TW_Scene* self );
