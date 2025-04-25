#include "../../ecs/scene.h"


// Creates a player component object.

TW_Player* TW_Player_Create()
{
    TW_Player* player = malloc( sizeof( TW_Player ) );
    player->parent = NULL;
    player->jumping = false;
    player->falling = false;
    return player;
}


// Frees resources used by a player object.
void TW_Player_Free( TW_Player* self )
{
    self->jumping = false;
    self->falling = false;
    self->parent = NULL;
    free( self );
}


// The think function for the player entity
void TW_Player_Think( TW_Entity* entity )
{
    if( entity != NULL )
    {
        // Collisions
        TW_Scene* parentScene = entity->parent;
        TW_Component* playerPlayer = TW_Entity_GetComponent( entity, TW_C_PLAYER );
        TW_Component* playerTransform = TW_Entity_GetComponent( entity, TW_C_TRANSFORM );
        TW_Component* playerVelocity = TW_Entity_GetComponent( entity, TW_C_VELOCITY );
        TW_Component* playerAnimation = TW_Entity_GetComponent( entity, TW_C_ANIMATION );

        // "Gravity"
        playerVelocity->velocity->acceleration->y += 1;
        if( playerVelocity->velocity->speed->y >= 12 )
        {
            playerVelocity->velocity->speed->y = 12;
        }

        if( parentScene != NULL )
        {
            for( int index = 0; index < parentScene->size; index++ )
            {
                if( entity != parentScene->entities[ index ] )
                {
                    if( TW_Collision_Check( entity, parentScene->entities[ index ] ) == true )
                    {
                        if( TW_Entity_GetComponent( parentScene->entities[ index ], TW_C_PLATFORM ) != NULL )
                        {
                            // FIX THIS JANK - Not a good collision implementation
                            TW_Component* targetTransform = TW_Entity_GetComponent( parentScene->entities[ index ], TW_C_TRANSFORM );
                            TW_Component* targetCollision = TW_Entity_GetComponent( parentScene->entities[ index ], TW_C_COLLISION );
                            if( playerVelocity->velocity->speed->y <= 0 && playerPlayer->player->jumping == true )
                            {
                                playerTransform->transform->position->y = targetTransform->transform->position->y + targetCollision->collision->position->y + targetCollision->collision->size->y;
                            }
                            else
                            {
                                playerTransform->transform->position->y = targetTransform->transform->position->y - playerAnimation->animation->spriteSheet->height;
                            }
                            playerPlayer->player->jumping = false;
                            playerVelocity->velocity->speed->y = 0;
                            playerVelocity->velocity->speed->y = 1;
                        }
                    }
                }
            }
        }

        // Input
        if( playerVelocity != NULL )
        {
            // Movement keys
            if( TW_InputHandler_CheckKeyPressed( SDLK_RSHIFT ) )
            {
                if( TW_GameState_PauseStatus() == false )
                {
                    TW_GameState_Pause();
                }
                else
                {
                    TW_GameState_Resume();
                }
                TW_Component* cTempAnimation = TW_Entity_GetComponent( entity, TW_C_ANIMATION );
                if( cTempAnimation != NULL )
                {
                    cTempAnimation->animation->paused = TW_GameState_PauseStatus();
                }
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_s ) )
            {
                playerVelocity->velocity->speed->y = 15;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_w ) )
            {
                playerVelocity->velocity->speed->y = -15;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_d ) )
            {
                playerVelocity->velocity->speed->x = 5;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_a ) )
            {
                playerVelocity->velocity->speed->x = -5;
            }

            if( TW_InputHandler_CheckKeyDepressed( SDLK_w ) || TW_InputHandler_CheckKeyDepressed( SDLK_s ) )
            {
                playerVelocity->velocity->speed->y = 0;
            }

            if( TW_InputHandler_CheckKeyDepressed( SDLK_a ) || TW_InputHandler_CheckKeyDepressed( SDLK_d ) )
            {
                playerVelocity->velocity->speed->x = 0;
            }

            // FIX THIS JANK - Jumping
            if( TW_InputHandler_CheckKeyDepressed( SDLK_SPACE) )
            {
                if( playerPlayer->player->jumping == false )
                {
                    playerVelocity->velocity->speed->y = -8;
                    playerVelocity->velocity->acceleration->y = -6;
                    playerPlayer->player->jumping = true;
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
    TW_Component* cPlayerCollision = TW_Component_Create( TW_C_COLLISION, playerCollision );
    TW_Entity_AddComponent( playerEntity, cPlayerCollision );

    TW_Think* playerThink = TW_Think_Create( TW_Player_Think );
    TW_Component* cPlayerThink = TW_Component_Create( TW_C_THINK, playerThink );
    TW_Entity_AddComponent( playerEntity, cPlayerThink );

    TW_Scene_AddEntity( target, playerEntity );
}