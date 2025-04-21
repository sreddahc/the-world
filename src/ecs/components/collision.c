#include "collision.h"


// Create a collision object based on provided parameters.
TW_Collision* TW_Collision_Create( int x, int y, int w, int h )
{
    TW_Collision* collision = malloc( sizeof( TW_Collision ) );

    collision->position = TW_Vector2_Create( x, y );
    collision->size = TW_Vector2_Create( w, h );
    collision->parent = NULL;

    return collision;
}


// Frees the resources used by a collision object.
void TW_Collision_Free( TW_Collision* self )
{
    self->parent = NULL;
    TW_Vector2_Free( self->size );
    TW_Vector2_Free( self->position );
    free( self );
}