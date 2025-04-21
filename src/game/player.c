#include "player.h"


// The think function for the player entity
void TW_Player_Think( TW_Component* component )
{
    if( component->parent != NULL )
    {
        TW_Component* velocityComponent = TW_Entity_GetComponent( component->parent, TW_C_VELOCITY );
        if( velocityComponent != NULL )
        {
            // Movement keys

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
void TW_Player_Create( TW_Scene* target )
{
    TW_Entity* entityPlayer = TW_Entity_Create();

    TW_Velocity* velocityPlayer = TW_Velocity_Create( 0, 0, 0, 0 );
    velocityPlayer->interval = 50;
    TW_Component* cVelocityPlayer = TW_Component_Create( TW_C_VELOCITY, velocityPlayer );
    TW_Entity_AddComponent( entityPlayer, cVelocityPlayer );

    TW_Sprite* spritePlayer = TW_Sprite_Create( "src/assets/images/sprites/player.png", 32, 32 );
    TW_Animation* animationPlayer = TW_Animation_Create( spritePlayer, 4, (int[]){ 0, 1, 2, 3 } );
    TW_Component* cPlayerAnimation = TW_Component_Create( TW_C_ANIMATION, animationPlayer );
    TW_Entity_AddComponent( entityPlayer, cPlayerAnimation );

    TW_Transform* transformPlayer = TW_Transform_Create( 230, 230, 0.0, 1.0 );
    TW_Component* cPlayerTransform = TW_Component_Create( TW_C_TRANSFORM, transformPlayer );
    TW_Entity_AddComponent( entityPlayer, cPlayerTransform );

    TW_Think* thinkPlayer = TW_Think_Create( TW_Player_Think );
    TW_Component* cThinkPlayer = TW_Component_Create( TW_C_THINK, thinkPlayer );
    TW_Entity_AddComponent( entityPlayer, cThinkPlayer );

    TW_Scene_AddEntity( target, entityPlayer );
}