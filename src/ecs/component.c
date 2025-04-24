#include "component.h"


// Creates a pointer to a component of specified type and value
TW_Component* TW_Component_Create( int type, void* value ){
    TW_Component* component = malloc( sizeof( TW_Component ) );
    component->type = type;
    switch ( component->type )
    {
        // Texture components
        case TW_C_ANIMATION:
            component->animation = value;
            component->animation->parent = component;
            break;

        case TW_C_SPRITE:
            component->sprite = value;
            component->sprite->parent = component;
            break;

        case TW_C_TEXT:
            component->text = value;
            component->text->parent = component;
            break;

        case TW_C_TEXTURE:
            component->texture = value;
            component->texture->parent = component;
            break;

        // Logic components
        case TW_C_COLLISION:
            component->collision = value;
            component->collision->parent = component;
            break;

        case TW_C_THINK:
            component->think = value;
            component->think->parent = component;
            break;

        case TW_C_TRANSFORM:
            component->transform = value;
            component->transform->parent = component;
            break;

        case TW_C_VELOCITY:
            component->velocity = value;
            component->velocity->parent = component;
            break;
        
        // Game components
        case TW_C_PLAYER:
            component->player = value;
            component->player->parent = component;
            break;

        default:
            break;
    }

    return component;
}


/**
 * TW_Component_GetParent - Given a component object, returns its parent. of one exists,
 *                          otherwise returns `NULL`.
 * 
 * Args:
 * - TW_Component*      - self          - Find the parent entity of this component
 * 
 * Returns:
 * - TW_Entity*         - Returns the parent entity if found, otherwise returns `NULL`
 */
TW_Entity* TW_Component_GetParent( TW_Component* self )
{
    if( self->parent != NULL )
    {
        return self->parent;
    }
    return NULL;
}


// If there is a visual aspect to the component... render it
void TW_Component_Render( TW_Component* self, TW_Transform* transform )
{
    switch ( self->type )
    {
        case TW_C_TEXTURE:
            TW_Texture_Render( self->texture, transform );
            break;

        case TW_C_TEXT:
            TW_Text_Render( self->text, transform );
            break;

        case TW_C_SPRITE:
            TW_Sprite_Render( self->sprite, transform );
            break;

        case TW_C_ANIMATION:
            TW_Animation_Render( self->animation, transform );
            break;

        default:
            break;
    }
}


// Run logic components
void TW_Component_RunLogic( TW_Component* self )
{
    switch( self->type )
    {
        case TW_C_THINK:
            TW_Think_Run( self->think, TW_Component_GetParent( self ) );
            break;

        default:
            break;
    }
}


// Run physics components
void TW_Component_RunPhysics( TW_Component* self )
{
    switch( self->type )
    {
        case TW_C_VELOCITY:
            TW_Velocity_Run( self->velocity, TW_Component_GetParent( self ) );
            break;

        case TW_C_COLLISION:
            // TW_Think_Run( self->think, TW_Component_GetParent( self ) );
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
        // Texture components
        case TW_C_ANIMATION:
            TW_Animation_Free( self->animation );
            break;

        case TW_C_SPRITE:
            TW_Sprite_Free( self->sprite );
            break;

        case TW_C_TEXTURE:
            TW_Texture_Free( self->texture );
            break;

        case TW_C_TEXT:
            TW_Text_Free( self->text );
            break;

        // Logic components
        case TW_C_COLLISION:
            TW_Collision_Free( self->collision );
            break;

        case TW_C_THINK:
            TW_Think_Free( self->think );
            break;

        case TW_C_TRANSFORM:
            TW_Transform_Free( self->transform );
            break;

        case TW_C_VELOCITY:
            TW_Velocity_Free( self->velocity );
            break;

        // Game components
        case TW_C_PLAYER:
            TW_Player_Free( self->player );
            break;

        default:
            break;
    }

    self->type = 0;
    free(self);
}