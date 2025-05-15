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
        TW_Component* vCollision = TW_Entity_GetComponent( entity, TW_C_VELOCITY );
        TW_Component* sCollision = TW_Entity_GetComponent( entity, TW_C_SPELL );

        // Projectile
        if( cCollision != NULL )
        {
            if( vCollision != NULL && sCollision != NULL )
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
                        // Change from collision projectile to impact
                        cCollision->destroy = true;
                        vCollision->velocity->speed->x = 0;
                        vCollision->velocity->speed->y = 0;
                        vCollision->velocity->acceleration->x = 0;
                        vCollision->velocity->acceleration->y = 0;
                        sCollision->spell->textureShoot->animation->hidden = true;
                        sCollision->spell->textureImpact->animation->hidden = false;
                    }
                }
            }
        }
        // Impact
        else
        {
            TW_Component* aCollision = TW_Entity_GetComponent( entity, TW_C_ANIMATION );
            if( aCollision != NULL )
            {
                if( sCollision->spell->textureImpact->animation->currentFrame == sCollision->spell->textureImpact->animation->animationSize - 1 )
                {
                    TW_Spell_DestroySpell( entity );
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

        TW_Spell* oSpell = TW_Spell_Create();
        TW_Component* cSpell = TW_Component_Create( TW_C_SPELL, oSpell );
        TW_Entity_AddComponent( entity, cSpell );

        TW_Sprite* oShoot = TW_Sprite_Create( "src/assets/images/sprites/magic.png", 32, 32 );
        TW_Animation* aShoot = TW_Animation_Create( oShoot, 3, (int[]){ 0, 1, 2 } );
        TW_Component* cShoot = TW_Component_Create( TW_C_ANIMATION, aShoot );
        oSpell->textureShoot = cShoot;
        TW_Entity_AddComponent( entity, cShoot );

        TW_Sprite* oImpact = TW_Sprite_Create( "src/assets/images/sprites/magic.png", 32, 32 );
        TW_Animation* aImpact = TW_Animation_Create( oImpact, 6, (int[]){ 3, 4, 5, 6, 7, 8 } );
        aImpact->loop = false;
        aImpact->hidden = true;
        TW_Component* cImpact = TW_Component_Create( TW_C_ANIMATION, aImpact );
        oSpell->textureImpact = cImpact;
        TW_Entity_AddComponent( entity, cImpact );

        TW_Transform* oTransform = TW_Transform_Create( tCaster->transform->position->x, tCaster->transform->position->y, 0.0, 1.0 );
        TW_Component* cTransform = TW_Component_Create( TW_C_TRANSFORM, oTransform );
        TW_Entity_AddComponent( entity, cTransform );

        TW_Collision* oCollision = TW_Collision_Create( 9, 9, 14, 14 );
        TW_Component* cCollision = TW_Component_Create( TW_C_COLLISION, oCollision );
        TW_Entity_AddComponent( entity, cCollision );

        TW_Think* oThink = TW_Think_Create( TW_Spell_Think );
        TW_Component* cThink = TW_Component_Create( TW_C_THINK, oThink );
        TW_Entity_AddComponent( entity, cThink );

        int casterDirection = tCaster->transform->flip == SDL_FLIP_HORIZONTAL ? -1 : 1;
        TW_Velocity* oVelocity = TW_Velocity_Create( casterDirection * 20, 0, 0, 0 );
        TW_Component* cVelocity = TW_Component_Create( TW_C_VELOCITY, oVelocity );
        TW_Entity_AddComponent( entity, cVelocity );

        TW_Scene_AddEntity( scene, entity );
    }
}


// Destroys a spell entity and removes it from the parent scene.
void TW_Spell_DestroySpell( TW_Entity* self )
{
    self->destroy = true;
}
