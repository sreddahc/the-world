#include "player.h"

// HERE BE SEGFAULTS

TW_Entity* TW_Player_Create()
{
    // Create player entity
    TW_Entity* entityPlayer = TW_Entity_Create();

    // Animations and sprites when called from here currently cause segfaults.
    // Temporary sprite based player created.

    // TW_Animation* gPlayer = TW_Animation_Create(
    //     TW_Sprite_Create( "src/images/sprites/player.png", 32, 32 ), 4, (int[]){ 0, 1, 2, 3 }
    // );

    TW_Sprite* spritePlayer = TW_Sprite_Create( "src/images/sprites/player.png", 32, 32 );

    TW_Component* componentPlayerSprite = TW_Component_Create( TW_C_SPRITE, spritePlayer );
    TW_Entity_AddComponent( entityPlayer, componentPlayerSprite );

    TW_Transform* transformPlayer = TW_Transform_Create( 100, 100, 0.0, 1.0 );
    TW_Component* componentPlayerTransform = TW_Component_Create( TW_C_TRANSFORM, transformPlayer );
    TW_Entity_AddComponent( entityPlayer, componentPlayerTransform );

    // TW_Animation* animationPlayer = TW_Animation_Create( spritePlayer, 4, (int[]){0, 1, 2, 3} );
    // TW_Component* componentPlayerAnimation = TW_Component_Create( TW_COMPONENT_ANIMATION, animationPlayer );
    // TW_Entity_AddComponent(entityPlayer, componentPlayerAnimation );

    return entityPlayer;
}