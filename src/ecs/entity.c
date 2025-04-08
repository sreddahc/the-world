#include "entity.h"


TW_Entity* TW_Entity_CreateEntity()
{
    TW_Entity* entity = malloc( sizeof( TW_Entity ) );
    entity->size = 0;
    entity->components = NULL;
    return entity;
}


void TW_Entity_AddComponent( TW_Entity* self, TW_Component* component )
{
    // should identify if the entity has already been added... if so don't add it.
    self->size += 1;
    if( self->size > 0 )
    {
        if( self->components == NULL )
        {
            self->components = malloc( self->size * sizeof( TW_Component ) );
            self->components[ self->size - 1 ] = component;
        }
        else
        {
            TW_Component* oldComponents = self->components;
            self->components = malloc( self->size * sizeof( TW_Component ) );
            memcpy( self->components, oldComponents, ( self->size - 1 ) * sizeof( TW_Component ) );
            self->components[ self->size - 1 ] = component;
        }
    }
}