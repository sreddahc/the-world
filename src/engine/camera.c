#include "camera.h"
#include "gamestate.h"
#include "level.h"
#include "../ecs/scene.h"
#include "maths.h"


static TW_Camera* gameCamera = NULL;


// Create a camera object.
void TW_Camera_Create( TW_Entity* target, int x, int y )
{
    gameCamera = malloc( sizeof( TW_Camera ) );
    gameCamera->target = target;
    gameCamera->size = TW_Vector2_Create( x, y );
}


// Frees the resources used by a camera object.
void TW_Camera_Free()
{
    gameCamera->target = NULL;
    TW_Vector2_Free( gameCamera->size );
    free( gameCamera );
}


// Set the target entity for the camera to follow.
void TW_Camera_SetTarget( TW_Entity* target )
{
    gameCamera->target = target;
}


// Set the size of the camera.
void TW_Camera_SetSize( int x, int y )
{
    TW_Vector2_Set( gameCamera->size, x, y );
}

// Acquire the camera offset.
int TW_Camera_GetOffset( enum TW_Axis axis )
{
    int offset = 0;
    if( gameCamera != NULL )
    {
        if( gameCamera->target != NULL )
        {
            TW_Component* tTarget = TW_Entity_GetComponent( gameCamera->target, TW_C_TRANSFORM );
            if( tTarget != NULL )
            {
                TW_Level* currentLevel = TW_GameState_GetLevel();
                if( gameCamera->size != NULL && currentLevel != NULL )
                {
                    int cameraMin = 0;
                    int cameraMax = 0;
                    int entityPos = 0;
                    if( axis == TW_AXIS_X )
                    {
                        cameraMin = 0;
                        cameraMax = currentLevel->size->x - ( gameCamera->size->x );
                        entityPos = tTarget->transform->position->x - ( gameCamera->size->x / 2 );
                    }
                    else
                    {
                        cameraMin = 0;
                        cameraMax = currentLevel->size->y - ( gameCamera->size->y );
                        entityPos = tTarget->transform->position->y - ( gameCamera->size->y / 2 );
                    }
                    if( entityPos < cameraMin )
                    {
                        offset = 0;
                    }
                    else if( entityPos > cameraMax )
                    {
                        offset = cameraMax;
                    }
                    else
                    {
                        offset = entityPos;
                    }
                }
            }
        }
    }
    return offset;
}
