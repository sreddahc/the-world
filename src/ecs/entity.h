#pragma once

#include "component.h"


// Type definitions

/**
 * TW_Entity - An entity
 * 
 * Elements:
 * - TW_Texture*        - texture       - The texture of the sprite
 * - TW_Coord*          - position      - The position of an object on the screen
 */
typedef struct TW_Entity {
    int size;
    TW_Component* components;
} TW_Entity;


// Function definitions


/**
 * TW_Entity_AddComponent - Given an entity and component, adds a component to the entity
 * 
 * Args:
 * - TW_Entity*         - self          - The entity to add a component to
 * - TW_Component*      - component     - The component to add to the entity
 */
void TW_Entity_AddComponent( TW_Entity* self, TW_Component* component );
