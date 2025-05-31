#include "../../ecs/scene.h"
#include "../../engine/level.h"


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
        TW_Component* tPlayer = TW_Entity_GetComponent( entity, TW_C_TRANSFORM );
        TW_Component* vPlayer = TW_Entity_GetComponent( entity, TW_C_VELOCITY );
        TW_Component* cPlayer = TW_Entity_GetComponent( entity, TW_C_COLLISION );

        // Is player on the ground?
        if( TW_Player_OnGroundCheck( entity ) == true )
        {
            vPlayer->velocity->speed->y = 0;
            pPlayer->player->jumping = false;
            pPlayer->player->onGround = true;
        }
        else
        {
            pPlayer->player->onGround = false;
        }

        // Is player outside the level?
        if( tPlayer != NULL && cPlayer != NULL )
        {
            TW_Level* currentLevel = TW_GameState_GetLevel();
            TW_Vector2* screenSize = NULL;
            if( currentLevel != NULL )
            {
                screenSize = currentLevel->size;
            }
            if( screenSize != NULL )
            {
                if(
                    ( tPlayer->transform->position->x + cPlayer->collision->position->x + cPlayer->collision->size->x < 0 ) ||
                    ( tPlayer->transform->position->y + cPlayer->collision->position->y + cPlayer->collision->size->y < 0 ) ||
                    ( tPlayer->transform->position->x + cPlayer->collision->position->x > screenSize->x ) ||
                    ( tPlayer->transform->position->y + cPlayer->collision->position->y > screenSize->y )
                )
                {
                    TW_Transform_SetPosition( tPlayer->transform, 35, 210 );
                }
            }
        }

        // Input
        if( vPlayer != NULL )
        {
            if( TW_InputHandler_CheckKeyDown( SDLK_a ) )
            {
                vPlayer->velocity->speed->x = -5;
                tPlayer->transform->flip = SDL_FLIP_HORIZONTAL;
            }

            if( TW_InputHandler_CheckKeyDown( SDLK_d ) )
            {
                vPlayer->velocity->speed->x = 5;
                tPlayer->transform->flip = SDL_FLIP_NONE;
            }

            if( TW_InputHandler_CheckKeyUp( SDLK_a ) || TW_InputHandler_CheckKeyUp( SDLK_d ) )
            {
                vPlayer->velocity->speed->x = 0;
            }

            if( TW_InputHandler_CheckKeyDown( SDLK_SPACE) )
            {
                if( ( pPlayer->player->jumping == false ) && ( pPlayer->player->onGround == true ) )
                {
                    vPlayer->velocity->speed->y = -8;
                    pPlayer->player->jumping = true;
                    pPlayer->player->onGround = false;
                    tPlayer->transform->position->y -= 1;
                }
            }

            // if( TW_InputHandler_CheckKeyUp( SDLK_LSHIFT ) )
            // {
            //     TW_Projectile_Generate( pPlayer->parent->parent, entity );
            // }

            if( TW_InputHandler_CheckKeyUp( SDLK_LSHIFT ) )
            {
                TW_Weapon_Generate( entity, TW_W_SWORD );
            }

            // FOR TESTING ONLY →

            if( TW_InputHandler_CheckMouseDown( 1 ) )
            {
                int x = 0;
                int y = 0;
                SDL_GetMouseState( &x, &y );
                tPlayer->transform->position->x = x;
                tPlayer->transform->position->y = y;
                vPlayer->velocity->speed->y = 0;
                pPlayer->player->jumping = false;
            }

            // FOR TESTING ONLY ←

            // Texture
            if( pPlayer->player->jumping )
            {
                pPlayer->player->textureWalking->animation->hidden = true;
                pPlayer->player->textureIdle->sprite->hidden = false;
                pPlayer->player->textureIdle->sprite->currentSprite = 0;
            }
            else
            {
                if( vPlayer->velocity->speed->x == 0 )
                {
                    pPlayer->player->textureWalking->animation->hidden = true;
                    pPlayer->player->textureIdle->sprite->hidden = false;
                    pPlayer->player->textureIdle->sprite->currentSprite = 1;
                }
                else
                {
                    pPlayer->player->textureWalking->animation->hidden = false;
                    pPlayer->player->textureIdle->sprite->hidden = true;
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

    // Textures

    // Idle
    TW_Sprite* sIdle = TW_Sprite_Create( "src/assets/images/sprites/knight.png", 32, 32 );
    sIdle->currentSprite = 1;
    TW_Component* cIdle = TW_Component_Create( TW_C_SPRITE, sIdle );
    playerPlayer->textureIdle = cIdle;
    TW_Entity_AddComponent( playerEntity, cIdle );

    // Walking
    TW_Sprite* sWalking = TW_Sprite_Create( "src/assets/images/sprites/knight.png", 32, 32 );
    TW_Animation* aWalking = TW_Animation_Create( sWalking, 4, (int[]){ 0, 1, 2, 1 } );
    aWalking->animationSpeed = 100;
    TW_Component* cWalking = TW_Component_Create( TW_C_ANIMATION, aWalking );
    playerPlayer->textureWalking = cWalking;
    TW_Entity_AddComponent( playerEntity, cWalking );

    // Properties

    TW_Velocity* playerVelocity = TW_Velocity_Create( 0, 0, 0, 1 );
    playerVelocity->interval = 50;
    TW_Component* cPlayerVelocity = TW_Component_Create( TW_C_VELOCITY, playerVelocity );
    TW_Entity_AddComponent( playerEntity, cPlayerVelocity );

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


// Check if player entity is on the ground
bool TW_Player_OnGroundCheck( TW_Entity* self )
{
    bool onGround = false;
    if( self != NULL )
    {
        TW_Scene* scene = self->parent;
        TW_Component* cPlayer = TW_Entity_GetComponent( self, TW_C_COLLISION );
        if( scene != NULL )
        {
            // Temporarily move the collision box down 1 pixel
            cPlayer->collision->position->y += 1;
            for( int index = 0; index < scene->size; index++ )
            {
                if( scene->entities[ index ] != self )
                {
                    if( scene->entities[ index ]->destroy == false )
                    {
                        TW_Component* pTarget = TW_Entity_GetComponent( scene->entities[ index ], TW_C_PLATFORM );
                        if( pTarget != NULL )
                        {
                            TW_Component* cTarget = TW_Entity_GetComponent( scene->entities[ index ], TW_C_COLLISION );
                            if( cTarget != NULL )
                            {
                                if( TW_Collision_Check( self, scene->entities[ index ] ) == true )
                                {
                                    onGround = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            // Return collision box back to original location.
            cPlayer->collision->position->y -= 1;
        }
    }

    return onGround;
}