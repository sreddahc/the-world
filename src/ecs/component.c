#include "component.h"


// Creates a pointer to a component of specified type and value
TW_Component* TW_Component_Create( int type, TW_Component_Value* value ){
    TW_Component* component = malloc( sizeof( TW_Component ) );
    component->type = type;
    switch ( component->type )
    {
        case TW_COMPONENT_TRANSFORM:
            component->transform = value;
            component->transform->parent = component;
            break;

        case TW_COMPONENT_TEXTURE:
            component->texture = value;
            component->texture->parent = component;
            break;

        case TW_COMPONENT_TEXT:
            component->text = value;
            component->text->parent = component;
            break;

            case TW_COMPONENT_SPRITE:
            component->sprite = value;
            component->sprite->parent = component;
            break;

        case TW_COMPONENT_ANIMATION:
            component->animation = value;
            component->animation->parent = component;
            break;

        default:
            break;
    }

    return component;
}


// If there is a visual aspect to the component... renders it
void TW_Component_Render( TW_Component* self, TW_Transform* transform )
{
    switch ( self->type )
    {
        case TW_COMPONENT_TEXTURE:
            TW_Texture_Render( self->texture, transform );
            break;

        case TW_COMPONENT_TEXT:
            TW_Text_Render( self->text, transform );
            break;

            case TW_COMPONENT_SPRITE:
            TW_Sprite_Render( self->sprite, transform );
            break;

        case TW_COMPONENT_ANIMATION:
            TW_Animation_Render( self->animation, transform );
            break;

        default:
            break;
    }
}


// Given a component, return a pointer to its parent entity object if it exists.
// If not, return `NULL`.
TW_Entity* TW_Component_GetParent( TW_Component* self )
{
    if( self->parent != NULL )
    {
        return self->parent;
    }

    return NULL;
}


// Frees resources for a given TW_Component
void TW_Component_Free( TW_Component* self )
{
    switch ( self->type )
    {
        case TW_COMPONENT_TRANSFORM:
            TW_Transform_Free( self->transform );
            break;

        case TW_COMPONENT_TEXTURE:
            TW_Texture_Free( self->texture );
            break;

        case TW_COMPONENT_TEXT:
            TW_Text_Free( self->text );
            break;

            case TW_COMPONENT_SPRITE:
            TW_Sprite_Free( self->sprite );
            break;

        case TW_COMPONENT_ANIMATION:
            TW_Animation_Free( self->animation );
            break;

        default:
            break;
    }
}