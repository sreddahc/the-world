#include "entity.h"


// Creates an TW_Entity object for all your component needs.
TW_Entity* TW_Entity_Create()
{
    TW_Entity* entity = malloc( sizeof( TW_Entity ) );
    entity->size = 0;
    entity->components = NULL;
    return entity;
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


// Free the resources used by an entity
void TW_Entity_Free( TW_Entity* self )
{}

// --- DEVELOPER ZONE !! DANGER !! COMMENTS MAY NOT EXIST ---

void TW_Entity_Render( TW_Entity* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        // Render visual components
        switch ( self->components[ index ]->type )
        {
        case TW_COMPONENT_TEXTURE:
            TW_Texture_Render( self->components[ index ]->value );
            break;

        case TW_COMPONENT_TEXT:
            TW_Text_Render( self->components[ index ]->value );
            break;
        
            case TW_COMPONENT_SPRITE:
            TW_Sprite_Render( self->components[ index ]->value );
            break;
        
        case TW_COMPONENT_ANIMATION:
            TW_Animation_Render( self->components[ index ]->value );
            break;
        
        default:
            break;
        }
    }
}