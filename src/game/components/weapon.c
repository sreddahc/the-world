#include "../../ecs/scene.h"

// Create a weapon object.
TW_Weapon* TW_Weapon_Create( TW_Entity* target, enum TW_WeaponType type )
{
    TW_Weapon* weapon = malloc( sizeof( TW_Weapon ) );
    weapon->parent = NULL;
    weapon->target = target;
    weapon->type = type;
    return weapon;
}

// Frees the resources used by a weapon object.
void TW_Weapon_Free( TW_Weapon* self )
{
    self->type = 0;
    self->parent = NULL;
    free( self );
}


// The think object for a weapon object.
void TW_Weapon_Think( TW_Entity* self )
{
    // Ensure that the weapon is still in the player's hand.
    TW_Component* tSelf = TW_Entity_GetComponent( self, TW_C_TRANSFORM );
    TW_Component* wSelf = TW_Entity_GetComponent( self, TW_C_WEAPON );
    if( tSelf != NULL && wSelf != NULL )
    {
        if( wSelf->weapon->target != NULL )
        {
            TW_Component* tTarget = TW_Entity_GetComponent( wSelf->weapon->target, TW_C_TRANSFORM );
            if( tTarget != NULL )
            {
                int direction = tTarget->transform->flip == SDL_FLIP_HORIZONTAL ? -1 : 1;
                tSelf->transform->flip = tTarget->transform->flip;
                tSelf->transform->position->x = tTarget->transform->position->x + direction * 13;
                tSelf->transform->position->y = tTarget->transform->position->y - 3;
            }
        }
    }
    
    // If animation is over... set the entity on the path to destruction.
    TW_Component* aSelf = TW_Entity_GetComponent( self, TW_C_ANIMATION );
    if( aSelf != NULL )
    {
        if( TW_Animation_LoopOver( aSelf->animation ) == true )
        {
            self->destroy = true;
        }
    }
}


// Generates a weapon entity and adds it to the scene of target entity.
void TW_Weapon_Generate( TW_Entity* target, enum TW_WeaponType type )
{
    TW_Component* pTarget = TW_Entity_GetComponent( target, TW_C_PLAYER );
    TW_Component* tTarget = TW_Entity_GetComponent( target, TW_C_TRANSFORM );

    if( pTarget != NULL && tTarget != NULL && target->parent != NULL )
    {
        TW_Entity* entity = TW_Entity_Create();

        TW_Weapon* oWeapon = TW_Weapon_Create( target, type );
        TW_Component* cWeapon = TW_Component_Create( TW_C_WEAPON, oWeapon );
        TW_Entity_AddComponent( entity, cWeapon );

        char imagePath[50] = "";
        switch ( type )
        {
            case TW_W_SWORD:
                strncpy( imagePath, "src/assets/images/sprites/sword.png", 50 );
                break;

            default:
                break;
        }
        TW_Animation* oAnimation = TW_Animation_Create(
            TW_Sprite_Create( imagePath, 32, 32 ),
            4,
            (int[]){ 0, 1, 2, 3 }
        );
        oAnimation->loop = false;
        oAnimation->animationSpeed = 50;
        TW_Component* cAnimation = TW_Component_Create( TW_C_ANIMATION, oAnimation );
        TW_Entity_AddComponent( entity, cAnimation );

        int direction = tTarget->transform->flip == SDL_FLIP_HORIZONTAL ? -1 : 1;
        TW_Transform* oTransform = TW_Transform_Create(
            tTarget->transform->position->x + direction * 13,
            tTarget->transform->position->y - 3,
            0.0,
            1.0
        );
        oTransform->flip = tTarget->transform->flip;
        TW_Component* cTransform = TW_Component_Create( TW_C_TRANSFORM, oTransform );
        TW_Entity_AddComponent( entity, cTransform );

        TW_Collision* oCollision = TW_Collision_Create( 0, 0, 32, 32 );
        TW_Component* cCollision = TW_Component_Create( TW_C_COLLISION, oCollision );
        TW_Entity_AddComponent( entity, cCollision );

        TW_Think* oThink = TW_Think_Create( TW_Weapon_Think );
        TW_Component* cThink = TW_Component_Create( TW_C_THINK, oThink );
        TW_Entity_AddComponent( entity, cThink );

        TW_Scene_AddEntity( target->parent, entity );
    }
}
