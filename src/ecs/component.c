#include "component.h"


// Creates a pointer to a component of specified type and value
TW_Component* TW_Component_Create( int type, TW_Component_Value* value ){
    TW_Component* component = malloc( sizeof( TW_Component ) );
    component->type = type;
    component->value = value;
    return component;
}


// If there is a visual aspect to the component... renders it
void TW_Component_Render( TW_Component* self )
{
    switch ( self->type )
    {
        case TW_COMPONENT_TEXTURE:
            TW_Texture_Render( self->value );
            break;

        case TW_COMPONENT_TEXT:
            TW_Text_Render( self->value );
            break;

            case TW_COMPONENT_SPRITE:
            TW_Sprite_Render( self->value );
            break;

        case TW_COMPONENT_ANIMATION:
            TW_Animation_Render( self->value );
            break;

        default:
            break;
    }
}


// Frees resources for a given TW_Component
void TW_Component_Free( TW_Component* self )
{
    switch ( self->type )
    {
        case TW_COMPONENT_TRANSFORM:
            TW_Transform_Free( self->value );
            break;

        case TW_COMPONENT_TEXTURE:
            TW_Texture_Free( self->value );
            break;

        case TW_COMPONENT_TEXT:
            TW_Text_Free( self->value );
            break;

            case TW_COMPONENT_SPRITE:
            TW_Sprite_Free( self->value );
            break;

        case TW_COMPONENT_ANIMATION:
            TW_Animation_Free( self->value );
            break;

        default:
            break;
    }
}