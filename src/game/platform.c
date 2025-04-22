#include "platform.h"


void TW_Platform_Create( TW_Scene* target, enum TW_PlatformPosition platformType, int x, int y )
{
    TW_Entity* platformEntity = TW_Entity_Create();

    TW_Sprite* platformSprite = TW_Sprite_Create( "src/assets/images/sprites/platforms.png", 70, 70 );
    platformSprite->currentSprite = platformType;
    TW_Component* cPlatformSprite = TW_Component_Create( TW_C_SPRITE, platformSprite );
    TW_Entity_AddComponent( platformEntity, cPlatformSprite );

    TW_Transform* platformTransform = TW_Transform_Create( x, y, 0.0, 1.0 );
    TW_Component* cPlatformTransform = TW_Component_Create( TW_C_TRANSFORM, platformTransform );
    TW_Entity_AddComponent( platformEntity, cPlatformTransform );

    TW_Collision* platformCollision = TW_Collision_Create( 0, 0, 70, 40 );
    TW_Component* cPlatformCollision = TW_Component_Create( TW_C_COLLISION, platformCollision );
    TW_Entity_AddComponent( platformEntity, cPlatformCollision );

    TW_Scene_AddEntity( target, platformEntity );
}
