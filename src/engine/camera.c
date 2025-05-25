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
                TW_Vector2* screenSize = TW_GameState_GetScreenSize();
                TW_Level* currentLevel = TW_GameState_GetLevel();
                if( screenSize != NULL && currentLevel != NULL )
                {
                    int minOffset = 0;
                    int maxOffset = 0;
                    int currentOffset = 0;
                    if( axis == TW_AXIS_X )
                    {
                        minOffset = 0;
                        maxOffset = currentLevel->size->x - ( screenSize->x );
                        currentOffset = tTarget->transform->position->x - ( screenSize->x / 2 );
                        
                    }
                    else
                    {
                        minOffset = 0;
                        maxOffset = currentLevel->size->y - ( screenSize->y );
                        currentOffset = tTarget->transform->position->y - ( screenSize->y / 2 );
                    }
                    if( currentOffset > minOffset )
                    {
                        if( currentOffset > maxOffset )
                        {
                            offset = maxOffset;
                        }
                        else
                        {
                            offset = currentOffset;
                        }
                    }
                }
            }
        }
    }
    return offset;
}
