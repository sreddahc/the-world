#include "../../ecs/scene.h"


// Create a projectile component object.
TW_Projectile* TW_Projectile_Create()
{
    TW_Projectile* projectile = malloc( sizeof( TW_Projectile ) );
    projectile->parent = NULL;
    projectile->textureDestroy = NULL;
    projectile->textureProjectile = NULL;
    return projectile;
}


// Frees the resources used by a projectile component.
void TW_Projectile_Free( TW_Projectile* self )
{
    self->parent = NULL;
    self->textureDestroy = NULL;
    self->textureProjectile = NULL;
    free( self );
}


void TW_Projectile_Think( TW_Entity* entity )
{
    if( entity != NULL )
    {
        TW_Component* cCollision = TW_Entity_GetComponent( entity, TW_C_COLLISION );
        TW_Component* cVelocity = TW_Entity_GetComponent( entity, TW_C_VELOCITY );
        TW_Component* cProjectile = TW_Entity_GetComponent( entity, TW_C_PROJECTILE );

        // Shoot Projectile
        if( cCollision != NULL && cVelocity != NULL && cProjectile != NULL )
        {
            for( int index = 0; index < cCollision->collision->collisionSize; index++ )
            {
                TW_Entity* targetEntity = cCollision->collision->collisions[ index ];
                TW_Component* obstacle = NULL;
                if( targetEntity != NULL )
                {
                    obstacle = TW_Entity_GetComponent( targetEntity, TW_C_PLATFORM );
                }
                if( obstacle != NULL )
                {
                    // Set projectile on path to destruction
                    cCollision->destroy = true;
                    cVelocity->velocity->speed->x = 0;
                    cVelocity->velocity->speed->y = 0;
                    cVelocity->velocity->acceleration->x = 0;
                    cVelocity->velocity->acceleration->y = 0;
                    cProjectile->projectile->textureProjectile->animation->hidden = true;
                    cProjectile->projectile->textureDestroy->animation->hidden = false;
                }
            }
        }
        // Destroy Projectile
        else
        {
            if( cProjectile->projectile->textureDestroy != NULL )
            {
                if( TW_Animation_LoopOver( cProjectile->projectile->textureDestroy->animation ) == true )
                {
                    TW_Projectile_Destroy( entity );
                }
            }
            else
            {
                TW_Projectile_Destroy( entity );
            }
        }
        TW_Component* cTransform = TW_Entity_GetComponent( entity, TW_C_TRANSFORM );
        if( cTransform != NULL )
        {
            TW_Vector2* screenSize = TW_GameState_GetScreenSize();
            if ( screenSize != NULL )
            {
                if
                (
                    cTransform->transform->position->x < 0 ||
                    cTransform->transform->position->x > screenSize->x ||
                    cTransform->transform->position->y < 0 ||
                    cTransform->transform->position->y > screenSize->y
                )
                {
                    TW_Projectile_Destroy( entity );
                }
            }
        }
    }
}


// Generates a projectile entity and adds it to target scene.
void TW_Projectile_Generate( TW_Scene* scene, TW_Entity* caster )
{
    TW_Component* pCaster = TW_Entity_GetComponent( caster, TW_C_PLAYER );
    TW_Component* tCaster = TW_Entity_GetComponent( caster, TW_C_TRANSFORM );

    if( pCaster != NULL && tCaster != NULL )
    {
        TW_Entity* entity = TW_Entity_Create();

        TW_Projectile* oProjectile = TW_Projectile_Create();
        TW_Component* cProjectile = TW_Component_Create( TW_C_PROJECTILE, oProjectile );
        TW_Entity_AddComponent( entity, cProjectile );

        TW_Animation* oShoot = TW_Animation_Create(
            TW_Sprite_Create( "src/assets/images/sprites/magic.png", 32, 32 ),
            3,
            (int[]){ 0, 1, 2 }
        );
        TW_Component* cShoot = TW_Component_Create( TW_C_ANIMATION, oShoot );
        oProjectile->textureProjectile = cShoot;
        TW_Entity_AddComponent( entity, cShoot );

        TW_Animation* oImpact = TW_Animation_Create( 
            TW_Sprite_Create( "src/assets/images/sprites/magic.png", 32, 32 ),
            6,
            (int[]){ 3, 4, 5, 6, 7, 8 }
        );
        oImpact->loop = false;
        oImpact->hidden = true;
        TW_Component* cImpact = TW_Component_Create( TW_C_ANIMATION, oImpact );
        oProjectile->textureDestroy = cImpact;
        TW_Entity_AddComponent( entity, cImpact );

        TW_Transform* oTransform = TW_Transform_Create( tCaster->transform->position->x, tCaster->transform->position->y, 0.0, 1.0 );
        TW_Component* cTransform = TW_Component_Create( TW_C_TRANSFORM, oTransform );
        TW_Entity_AddComponent( entity, cTransform );

        TW_Collision* oCollision = TW_Collision_Create( 9, 9, 14, 14 );
        TW_Component* cCollision = TW_Component_Create( TW_C_COLLISION, oCollision );
        TW_Entity_AddComponent( entity, cCollision );

        TW_Think* oThink = TW_Think_Create( TW_Projectile_Think );
        TW_Component* cThink = TW_Component_Create( TW_C_THINK, oThink );
        TW_Entity_AddComponent( entity, cThink );

        int casterDirection = tCaster->transform->flip == SDL_FLIP_HORIZONTAL ? -1 : 1;
        TW_Velocity* oVelocity = TW_Velocity_Create( casterDirection * 20, 0, 0, 0 );
        TW_Component* cVelocity = TW_Component_Create( TW_C_VELOCITY, oVelocity );
        TW_Entity_AddComponent( entity, cVelocity );

        TW_Scene_AddEntity( scene, entity );
    }
}


// Destroys a projectile entity and removes it from the parent scene.
void TW_Projectile_Destroy( TW_Entity* self )
{
    self->destroy = true;
}
