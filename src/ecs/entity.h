#pragma once

#include "component.h"


// Type definitions

typedef struct TW_Scene TW_Scene;

/**
 * \brief An entity
 * 
 * \param size `int` – Size of the entity
 * \param destroy `bool` –  Should this entity be destroyed during clean up? `true` if so
 * \param parent `TW_Scene*` – Parent scene the entity belongs to
 * \param components `TW_Component**` – Components in the entity
 */
typedef struct TW_Entity {
    int size;
    bool destroy;
    TW_Scene* parent;
    TW_Component** components;
} TW_Entity;


// Function definitions

/**
 * \brief Creates an TW_Entity object for all your component needs.
 * 
 * \returns `TW_Entity*` – Returns an empty entity
 */
TW_Entity* TW_Entity_Create();


/**
 * \brief Free the resources used by an entity
 * 
 * \param self `TW_Entity*` – The entity to free
 */
void TW_Entity_Free( TW_Entity* self );


/**
 * \brief Given an entity and component, adds a component to the entity.
 * 
 * \param self `TW_Entity*` – The entity to add a component to
 * \param component `TW_Component*` – The component to add to the entity
 */
void TW_Entity_AddComponent( TW_Entity* self, TW_Component* component );


/**
 * \brief Given an entity and component type search the entity for that component.
 *        If found, return a pointer to that component, otherwise return `NULL`.
 * 
 * \param self `TW_Entity*` – The entity to search
 * \param type `TW_ComponentType` – The `TW_Component_Type` to search for
 */
TW_Component* TW_Entity_GetComponent( TW_Entity* self, enum TW_ComponentType type );


/**
 * \brief Run logic components in an entity
 * 
 * \param self `TW_Entity*` – Run logic components in this entity
 */
void TW_Entity_RunLogic( TW_Entity* self );


/**
 * \brief Run physics components in an entity
 * 
 * \param self `TW_Entity*` – Run physics components in this entity
 */
void TW_Entity_RunPhysics( TW_Entity* self );


/**
 * \brief Renders any entities with visual components
 * 
 * \param self `TW_Entity*` – The entity to render
 */
void TW_Entity_Render( TW_Entity* self );


/**
 * \brief Clear state based components in entity so they're ready for the next game loop.
 * 
 * \param self `TW_Entity*` – Clear components in this entity
 */
void TW_Entity_Clear( TW_Entity* self );
