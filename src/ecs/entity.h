#pragma once

#include "component.h"


// Type definitions

/**
 * TW_Entity - An entity
 * 
 * Elements:
 * - TW_Texture*        - texture       - The texture of the sprite
 * - TW_Component**     - componenets   - The components
 */
typedef struct TW_Entity {
    int size;
    TW_Component** components;
} TW_Entity;


// Function definitions

/**
 * TW_Entity_CreateEntity - Creates an TW_Entity object for all your component needs.
 * 
 * Returns:
 * - TW_Entity*         - Returns an empty entity
 */
TW_Entity* TW_Entity_CreateEntity();


/**
 * TW_Entity_AddComponent - Given an entity and component, adds a component to the entity.
 * 
 * Args:
 * - TW_Entity*         - self          - The entity to add a component to
 * - TW_Component*      - component     - The component to add to the entity
 */
void TW_Entity_AddComponent( TW_Entity* self, TW_Component* component );


/**
 * TW_Entity_Free - Free the resources used by an entity
 * 
 * Args:
 * - TW_Entity*         - self          - The entity to free
 */
void TW_Entity_Free( TW_Entity* self );