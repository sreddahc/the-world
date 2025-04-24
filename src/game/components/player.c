#include "player.h"


// The think function for the player entity
void TW_Player_Think( TW_Entity* entity )
{
    if( entity != NULL )
    {
        TW_Component* velocityComponent = TW_Entity_GetComponent( entity, TW_C_VELOCITY );
        if( velocityComponent != NULL )
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

            if( TW_InputHandler_CheckKeyPressed( SDLK_w ) )
            {
                velocityComponent->velocity->speed->y = -5;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_s ) )
            {
                velocityComponent->velocity->speed->y = 5;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_d ) )
            {
                velocityComponent->velocity->speed->x = 5;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_a ) )
            {
                velocityComponent->velocity->speed->x = -5;
            }

            if( TW_InputHandler_CheckKeyDepressed( SDLK_w ) || TW_InputHandler_CheckKeyDepressed( SDLK_s ) )
            {
                velocityComponent->velocity->speed->y = 0;
            }

            if( TW_InputHandler_CheckKeyDepressed( SDLK_a ) || TW_InputHandler_CheckKeyDepressed( SDLK_d ) )
            {
                velocityComponent->velocity->speed->x = 0;
            }
        }
    }
}


// Creates a player entity and adds it to target scene
void TW_Player_Create( TW_Scene* target, int x, int y )
{
    TW_Entity* playerEntity = TW_Entity_Create();

    TW_Velocity* playerVelocity = TW_Velocity_Create( 0, 0, 0, 0 );
    playerVelocity->interval = 50;
    TW_Component* cPlayerVelocity = TW_Component_Create( TW_C_VELOCITY, playerVelocity );
    TW_Entity_AddComponent( playerEntity, cPlayerVelocity );

    TW_Sprite* playerSprite = TW_Sprite_Create( "src/assets/images/sprites/knight.png", 32, 32 );
    TW_Animation* playerAnimation = TW_Animation_Create( playerSprite, 4, (int[]){ 0, 1, 2, 1 } );
    TW_Component* cPlayerAnimation = TW_Component_Create( TW_C_ANIMATION, playerAnimation );
    TW_Entity_AddComponent( playerEntity, cPlayerAnimation );

    TW_Transform* playerTransform = TW_Transform_Create( x, y, 0.0, 1.0 );
    TW_Component* cPlayerTransform = TW_Component_Create( TW_C_TRANSFORM, playerTransform );
    TW_Entity_AddComponent( playerEntity, cPlayerTransform );

    TW_Collision* playerCollision = TW_Collision_Create( 0, 0, playerSprite->width, playerSprite->height );
    TW_Component* cPlayerCollision = TW_Component_Create( TW_C_COLLISION, playerCollision );
    TW_Entity_AddComponent( playerEntity, cPlayerCollision );

    TW_Think* playerThink = TW_Think_Create( TW_Player_Think );
    TW_Component* cPlayerThink = TW_Component_Create( TW_C_THINK, playerThink );
    TW_Entity_AddComponent( playerEntity, cPlayerThink );

    TW_Scene_AddEntity( target, playerEntity );
}