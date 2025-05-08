#include "../../ecs/scene.h"


// Creates a player component object.

TW_Player* TW_Player_Create()
{
    TW_Player* player = malloc( sizeof( TW_Player ) );
    player->parent = NULL;
    player->jumping = false;
    return player;
}


// Frees resources used by a player object.
void TW_Player_Free( TW_Player* self )
{
    self->jumping = false;
    self->parent = NULL;
    free( self );
}


// The think function for the player entity
void TW_Player_Think( TW_Entity* entity )
{
    if( entity != NULL )
    {
        // Components required for thinking
        TW_Component* pPlayer = TW_Entity_GetComponent( entity, TW_C_PLAYER );
        TW_Component* pVelocity = TW_Entity_GetComponent( entity, TW_C_VELOCITY );

        // Input
        if( pVelocity != NULL )
        {
            if( TW_InputHandler_CheckKeyDown( SDLK_a ) )
            {
                pVelocity->velocity->speed->x = -5;
            }

            if( TW_InputHandler_CheckKeyDown( SDLK_d ) )
            {
                pVelocity->velocity->speed->x = 5;
            }

            if( TW_InputHandler_CheckKeyUp( SDLK_a ) || TW_InputHandler_CheckKeyUp( SDLK_d ) )
            {
                pVelocity->velocity->speed->x = 0;
            }

            if( TW_InputHandler_CheckKeyDown( SDLK_SPACE) )
            {
                if( pPlayer->player->jumping == false && pPlayer->player->onGround == true )
                {
                    pVelocity->velocity->speed->y = -8;
                    pPlayer->player->jumping = true;
                    pPlayer->player->onGround = false;
                }
            }
        }
    }
}


// Creates a player entity with all required components and adds it to target scene.
void TW_Scene_GeneratePlayer( TW_Scene* target, int x, int y )
{
    TW_Entity* playerEntity = TW_Entity_Create();

    TW_Player* playerPlayer = TW_Player_Create();
    TW_Component* cPlayerPlayer = TW_Component_Create( TW_C_PLAYER, playerPlayer );
    TW_Entity_AddComponent( playerEntity, cPlayerPlayer );

    TW_Velocity* playerVelocity = TW_Velocity_Create( 0, 0, 0, 1 );
    playerVelocity->interval = 50;
    TW_Component* cPlayerVelocity = TW_Component_Create( TW_C_VELOCITY, playerVelocity );
    TW_Entity_AddComponent( playerEntity, cPlayerVelocity );

    TW_Sprite* playerSprite = TW_Sprite_Create( "src/assets/images/sprites/knight.png", 32, 32 );
    TW_Animation* playerAnimation = TW_Animation_Create( playerSprite, 4, (int[]){ 0, 1, 2, 1 } );
    playerAnimation->animationSpeed = 100;
    TW_Component* cPlayerAnimation = TW_Component_Create( TW_C_ANIMATION, playerAnimation );
    TW_Entity_AddComponent( playerEntity, cPlayerAnimation );

    TW_Transform* playerTransform = TW_Transform_Create( x, y, 0.0, 1.0 );
    TW_Component* cPlayerTransform = TW_Component_Create( TW_C_TRANSFORM, playerTransform );
    TW_Entity_AddComponent( playerEntity, cPlayerTransform );

    TW_Collision* playerCollision = TW_Collision_Create( 7, 0, 17, 32 );
    playerCollision->hasPhysics = true;
    TW_Component* cPlayerCollision = TW_Component_Create( TW_C_COLLISION, playerCollision );
    TW_Entity_AddComponent( playerEntity, cPlayerCollision );

    TW_Think* playerThink = TW_Think_Create( TW_Player_Think );
    TW_Component* cPlayerThink = TW_Component_Create( TW_C_THINK, playerThink );
    TW_Entity_AddComponent( playerEntity, cPlayerThink );

    TW_Scene_AddEntity( target, playerEntity );
}
