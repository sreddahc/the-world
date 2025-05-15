#include "entity.h"


// Creates an TW_Entity object for all your component needs.
TW_Entity* TW_Entity_Create()
{
    TW_Entity* entity = malloc( sizeof( TW_Entity ) );
    entity->size = 0;
    entity->destroy = false;
    entity->parent = NULL;
    entity->components = NULL;
    return entity;
}


// Free the resources used by an entity
void TW_Entity_Free( TW_Entity* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        TW_Component_Free( self->components[ index ] );
    }
    self->size = 0;
    self->destroy = false;
    self->parent = NULL;
    free( self );
}


// Given an entity and component, adds a component to the entity.
void TW_Entity_AddComponent( TW_Entity* self, TW_Component* component )
{
    self->size += 1;
    if( self->size > 0 )
    {
        // Create space and add components. Memory handling for existing components.
        if( self->components == NULL )
        {
            self->components = malloc( self->size * sizeof( TW_Component* ) );
        }
        else
        {
            TW_Component** oldComponents = self->components;
            self->components = malloc( self->size * sizeof( TW_Component* ) );
            memcpy( self->components, oldComponents, ( self->size - 1 ) * sizeof( TW_Component* ) );
            free( oldComponents );
        }
        self->components[ self->size - 1 ] = component;
        component->parent = self;
    }
}


// Given an entity and component type search the entity for that component.
// If found, return a pointer to that component, otherwise return `NULL`.
TW_Component* TW_Entity_GetComponent( TW_Entity* self, enum TW_ComponentType type )
{
    for( int index = 0; index < self->size; index++ )
    {
        if( self->components[ index ]->type == type )
        {
            return self->components[ index ];
        }
    }
    return NULL;
}


// Run logic components in an entity
void TW_Entity_RunLogic( TW_Entity* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        TW_Component_RunLogic( self->components[ index ] );
    }
}


// Run physics components in an entity
void TW_Entity_RunPhysics( TW_Entity* self )
{
    // Collect physics components to run in a specific order
    TW_Component* collision = NULL;
    TW_Component* velocity = NULL;
    for( int index = 0; index < self->size; index++ )
    {
        switch ( self->components[ index ]->type )
        {
            case TW_C_COLLISION:
                collision = self->components[ index ];
                break;

            case TW_C_VELOCITY:
                velocity = self->components[ index ];
                break;

            default:
                break;
        }
    }
    TW_Component_RunPhysics( velocity );
    TW_Component_RunPhysics( collision );
}


// Renders any entities with visual components
void TW_Entity_Render( TW_Entity* self )
{
    TW_Component* transformComponent = TW_Entity_GetComponent( self, TW_C_TRANSFORM );
    TW_Transform* transform = NULL;
    if( transformComponent != NULL )
    {
        transform = transformComponent->transform;
    }

    for( int index = 0; index < self->size; index++ )
    {
        TW_Component_Render( self->components[ index ], transform );
    }
}


// Clear state based components in entity so they're ready for the next game loop.
void TW_Entity_Clear( TW_Entity* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        TW_Component_Clear( self->components[ index ] );
    }
}
