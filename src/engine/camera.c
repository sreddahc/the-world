#include "camera.h"
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
                if( axis == TW_AXIS_X )
                {
                    int tempOffset = tTarget->transform->position->x - ( screenSize->x / 2 );
                    if( tempOffset > 0 )
                    {
                        offset = tempOffset;
                    }
                }
                else
                {
                    int tempOffset = tTarget->transform->position->y - ( screenSize->y / 2 );
                    if( tempOffset > 0 )
                    {
                        offset = tempOffset;
                    }
                }
            }
        }
    }
    return offset;
}
