#include "../../ecs/scene.h"


// Create a spell component object.
TW_Spell* TW_Spell_Create()
{
    TW_Spell* spell = malloc( sizeof( TW_Spell ) );
    spell->parent = NULL;
    spell->textureImpact = NULL;
    spell->textureShoot = NULL;
    return spell;
}


// Frees the resources used by a spell component.
void TW_Spell_Free( TW_Spell* self )
{
    self->parent = NULL;
    self->textureImpact = NULL;
    self->textureShoot = NULL;
    free( self );
}


void TW_Spell_Think( TW_Entity* entity )
{
    if( entity != NULL )
    {
        TW_Component* cCollision = TW_Entity_GetComponent( entity, TW_C_COLLISION );
        TW_Component* aCollision = TW_Entity_GetComponent( entity, TW_C_ANIMATION );

        if( cCollision != NULL && aCollision != NULL )
        {
            for( int index = 0; index < cCollision->collision->collisionCount; index++ )
            {
                TW_Entity* targetEntity = cCollision->collision->collisions[ index ];
                TW_Component* obstacle = NULL;
                if( targetEntity != NULL )
                {
                    obstacle = TW_Entity_GetComponent( targetEntity, TW_C_PLATFORM );
                }
                if( obstacle != NULL )
                {
                    if( aCollision != NULL )
                    {
                        TW_Spell_DestroySpell( entity );
                    }
                }
            }
        }
    }
}


// Generates a spell entity and adds it to target scene.
void TW_Spell_GenerateSpell( TW_Scene* scene, TW_Entity* caster )
{
    TW_Component* pCaster = TW_Entity_GetComponent( caster, TW_C_PLAYER );
    TW_Component* tCaster = TW_Entity_GetComponent( caster, TW_C_TRANSFORM );

    if( pCaster != NULL && tCaster != NULL )
    {
        TW_Entity* entity = TW_Entity_Create();

        TW_Sprite* sprite = TW_Sprite_Create( "src/assets/images/sprites/magic.png", 32, 32 );
        TW_Animation* animation = TW_Animation_Create( sprite, 3, (int[]){ 0, 1, 2 } );
        TW_Component* cAnimation = TW_Component_Create( TW_C_ANIMATION, animation );
        TW_Entity_AddComponent( entity, cAnimation );

        TW_Transform* transform = TW_Transform_Create( tCaster->transform->position->x, tCaster->transform->position->y, 0.0, 1.0 );
        TW_Component* cTransform = TW_Component_Create( TW_C_TRANSFORM, transform );
        TW_Entity_AddComponent( entity, cTransform );

        TW_Collision* collision = TW_Collision_Create( 9, 9, 14, 14 );
        TW_Component* cCollision = TW_Component_Create( TW_C_COLLISION, collision );
        TW_Entity_AddComponent( entity, cCollision );

        TW_Think* think = TW_Think_Create( TW_Spell_Think );
        TW_Component* cThink = TW_Component_Create( TW_C_THINK, think );
        TW_Entity_AddComponent( entity, cThink );

        int casterDirection = tCaster->transform->flip == SDL_FLIP_HORIZONTAL ? -1 : 1;
        TW_Velocity* velocity = TW_Velocity_Create( casterDirection * 20, 0, 0, 0 );
        TW_Component* cVelocity = TW_Component_Create( TW_C_VELOCITY, velocity );
        TW_Entity_AddComponent( entity, cVelocity );

        TW_Scene_AddEntity( scene, entity );
    }
}


// Destroys a spell entity and removes it from the parent scene.
void TW_Spell_DestroySpell( TW_Entity* self )
{
    self->destroy = true;
}
