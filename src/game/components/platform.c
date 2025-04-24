#include "../../ecs/scene.h"


// Platform object initialised
TW_Platform* TW_Platform_Create()
{
    TW_Platform* platform = malloc( sizeof( TW_Platform ) );
    platform->parent = NULL;
    return platform;
}


// Free the resources used by a platform object
void TW_Platform_Free( TW_Platform* self )
{
    self->parent = NULL;
    free( self );
}


// Create a platform entity at position x and y in target scene
void TW_Scene_GeneratePlatform( TW_Scene* target, enum TW_PlatformPosition platformType, int x, int y )
{
    TW_Entity* platformEntity = TW_Entity_Create();

    TW_Platform* platformPlatform = TW_Platform_Create();
    TW_Component* cPlatformPlatform = TW_Component_Create( TW_C_PLATFORM, platformPlatform );
    TW_Entity_AddComponent( platformEntity, cPlatformPlatform );

    TW_Sprite* platformSprite = TW_Sprite_Create( "src/assets/images/sprites/platform.png", 35, 35 );
    platformSprite->currentSprite = platformType;
    TW_Component* cPlatformSprite = TW_Component_Create( TW_C_SPRITE, platformSprite );
    TW_Entity_AddComponent( platformEntity, cPlatformSprite );

    TW_Transform* platformTransform = TW_Transform_Create( x, y, 0.0, 1.0 );
    TW_Component* cPlatformTransform = TW_Component_Create( TW_C_TRANSFORM, platformTransform );
    TW_Entity_AddComponent( platformEntity, cPlatformTransform );

    TW_Collision* platformCollision = TW_Collision_Create( 0, 0, 35, 20 );
    TW_Component* cPlatformCollision = TW_Component_Create( TW_C_COLLISION, platformCollision );
    TW_Entity_AddComponent( platformEntity, cPlatformCollision );

    TW_Scene_AddEntity( target, platformEntity );
}
