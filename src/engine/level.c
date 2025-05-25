#include "level.h"
#include "maths.h"


// Create the level object.
TW_Level* TW_Level_Create( TW_Scene* scene, int x, int y )
{
    TW_Level* level = malloc( sizeof( TW_Level ) );
    level->size = TW_Vector2_Create( x, y );
    level->scene = scene;
    return level;
}


// Free the resources used by a level object.
void TW_Level_Free( TW_Level* self )
{
    TW_Vector2_Free( self->size );
    self->scene = NULL;
    free( self );
}


// Set the size of the level object.
void TW_Level_SetSize( TW_Level* self, int x, int y )
{
    TW_Vector2_Set( self->size, x, y );
}


// Set the scene of the level object.
void TW_Level_SetScene( TW_Level* self, TW_Scene* scene )
{
    self->scene = scene;
}


// Return the scene associated with a level.
TW_Scene* TW_Level_GetScene( TW_Level* self )
{
    if( self != NULL )
    {
        return self->scene;
    }
    return NULL;
}
