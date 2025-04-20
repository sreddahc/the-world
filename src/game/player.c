#include "player.h"


void TW_Player_Think( TW_Component* component )
{
    if( component->parent != NULL )
    {
        TW_Component* transformComponent = TW_Entity_GetComponent( component->parent, TW_C_TRANSFORM );
        if( transformComponent != NULL )
        {
            if( TW_InputHandler_CheckKeyPressed( SDLK_w ) )
            {
                transformComponent->transform->position->y -= 5;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_s ) )
            {
                transformComponent->transform->position->y += 5;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_a ) )
            {
                transformComponent->transform->position->x -= 5;
            }

            if( TW_InputHandler_CheckKeyPressed( SDLK_d ) )
            {
                transformComponent->transform->position->x += 5;
            }
        }
    }
}


TW_Entity* TW_Player_Create()
{
    TW_Entity* entityPlayer = TW_Entity_Create();

    TW_Sprite* spritePlayer = TW_Sprite_Create( "src/images/sprites/player.png", 32, 32 );
    TW_Animation* animationPlayer = TW_Animation_Create( spritePlayer, 4, (int[]){ 0, 1, 2, 3 } );
    TW_Component* cPlayerAnimation = TW_Component_Create( TW_C_ANIMATION, animationPlayer );
    TW_Entity_AddComponent( entityPlayer, cPlayerAnimation );

    TW_Transform* transformPlayer = TW_Transform_Create( 230, 230, 0.0, 1.0 );
    TW_Component* cPlayerTransform = TW_Component_Create( TW_C_TRANSFORM, transformPlayer );
    TW_Entity_AddComponent( entityPlayer, cPlayerTransform );

    TW_Think* thinkPlayer = TW_Think_Create( TW_Player_Think );
    TW_Component* cThinkPlayer = TW_Component_Create( TW_C_THINK, thinkPlayer );
    TW_Entity_AddComponent( entityPlayer, cThinkPlayer );

    return entityPlayer;
}