#include "../../ecs/scene.h"


// Create fountain object.
TW_Fountain* TW_Fountain_Create()
{
    TW_Fountain* fountain = malloc( sizeof( TW_Fountain ) );
    fountain->parent = NULL;
    fountain->type = 0;
    fountain->empty = false;
    fountain->cooldown = 0;
    fountain->textureEmpty = NULL;
    fountain->textureFull = NULL;
    return fountain;
}


// Free the resources used by a fountain object.
void TW_Fountain_Free( TW_Fountain* self  )
{
    self->parent = NULL;
    self->type = 0;
    self->empty = false;
    self->cooldown = 0;
    self->textureEmpty = NULL;
    self->textureFull = NULL;
    free( self );
}


// Generates a fountain entity of type at x and y position in the target scene.
void TW_Fountain_Generate( TW_Scene* target, enum TW_PowerType type, int x, int y )
{
    TW_Entity* entity = TW_Entity_Create();

    TW_Fountain* fountain = TW_Fountain_Create();
    fountain->type = type;
    switch (type)
    {
        case TW_PWR_MOON:
            fountain->cooldown = 20;
            break;

        case TW_PWR_SUN:
            fountain->cooldown = 10;
            break;

        default:
            break;
    }
    TW_Component* cFountain = TW_Component_Create( TW_C_FOUNTAIN, fountain );
    TW_Entity_AddComponent( entity, cFountain );

    // Textures

    // Empty
    TW_Sprite* spriteEmpty = TW_Sprite_Create( "src/assets/images/sprites/fountain.png", 32, 32 );
    TW_Component* cEmpty = TW_Component_Create( TW_C_SPRITE, spriteEmpty );
    TW_Entity_AddComponent( entity, cEmpty );
    spriteEmpty->hidden = !fountain->empty;
    spriteEmpty->currentSprite = 0;

    // Full
    TW_Sprite* spriteFull = TW_Sprite_Create( "src/assets/images/sprites/fountain.png", 32, 32 );
    int animationFrames[2] = { 0 , 0 };
    switch (type)
    {
        case TW_PWR_MOON:
            animationFrames[0] = 1;
            animationFrames[1] = 2;
            break;

        case TW_PWR_SUN:
            animationFrames[0] = 3;
            animationFrames[1] = 4;
            break;

        default:
            break;
    }
    TW_Animation* animationFull = TW_Animation_Create( spriteFull, 2, animationFrames );
    TW_Component* cFull = TW_Component_Create( TW_C_ANIMATION, animationFull );
    TW_Entity_AddComponent( entity, cFull );
    animationFull->animationSpeed = 120;
    animationFull->hidden = fountain->empty;

    TW_Transform* transform = TW_Transform_Create( x, y + 8 , 0.0, 1.0 );
    TW_Component* cTransform = TW_Component_Create( TW_C_TRANSFORM, transform );
    TW_Entity_AddComponent( entity, cTransform );

    TW_Scene_AddEntity( target, entity );

}