#include "player.h"

// HERE BE SEGFAULTS

TW_Entity* TW_Player_Create()
{
    // Create player entity
    // TW_Entity* playerEntity = TW_Entity_Create();

    TW_Animation* gPlayer = TW_Animation_Create( TW_Sprite_Create( "src/images/sprites/player.png", 32, 32 ), 4, (int[]){ 0, 1, 2, 3 } );

    TW_Entity* entityPlayer = TW_Entity_Create();
    TW_Entity_AddComponent( entityPlayer, TW_Component_Create( TW_COMPONENT_ANIMATION, gPlayer ) );
    TW_Entity_AddComponent( entityPlayer, TW_Component_Create( TW_COMPONENT_TRANSFORM, TW_Transform_Create( 200, 200, 0.0, 1.0 ) ) );

    // // Add animation component
    // TW_Entity_AddComponent(
    //     playerEntity,
    //     TW_Component_Create( TW_COMPONENT_ANIMATION, TW_Animation_Create(
    //         TW_Sprite_Create( "src/images/sprites/player.png", 32, 32 ),
    //         4,
    //         (int[]){ 0, 1, 2, 3 }
    // ) ) );

    // // Add transform component
    // TW_Transform* playerTransform = TW_Transform_Create( 200, 200, 0.0, 1.0 );
    // TW_Entity_AddComponent( playerEntity, TW_Component_Create( TW_COMPONENT_ANIMATION, playerAnimation ) );

    // Add think component
    // TO DO

    return entityPlayer;
}