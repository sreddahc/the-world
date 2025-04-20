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
 * TW_Entity_Create - Creates an TW_Entity object for all your component needs.
 * 
 * Returns:
 * - TW_Entity*         - Returns an empty entity
 */
TW_Entity* TW_Entity_Create();


/**
 * TW_Entity_Free - Free the resources used by an entity
 * 
 * Args:
 * - TW_Entity*         - self          - The entity to free
 */
void TW_Entity_Free( TW_Entity* self );


/**
 * TW_Entity_AddComponent - Given an entity and component, adds a component to the entity.
 * 
 * Args:
 * - TW_Entity*         - self          - The entity to add a component to
 * - TW_Component*      - component     - The component to add to the entity
 */
void TW_Entity_AddComponent( TW_Entity* self, TW_Component* component );


// --- DEVELOPER ZONE !! DANGER !! COMMENTS MAY NOT EXIST ---

/**
 * TW_Entity_GetComponent - Given an entity and component type search the entity for
 * that component. If found, return a pointer to that component, otherwise return `NULL`.
 * 
 * Args:
 * TW_Entity*           - self          - The entity to search
 * int                  - type          - The TW_Component_Type to search for
 */
TW_Component* TW_Entity_GetComponent( TW_Entity* self, int type );


/**
 * TW_Component_Render - Renders any entities with visual components
 * 
 * Args:
 * - TW_Entity*             - self          - The TW_Component to render
 */
void TW_Entity_Render( TW_Entity* self );


/**
 * TW_Component_Run - Run logic components in TW_Entity
 * 
 * Args:
 * - TW_Entity*             - self          - The TW_Component to run
 */
void TW_Entity_Run( TW_Entity* self );
