#include "transform.h"


// Creates a TW_Transform object with the specified values
TW_Transform* TW_Transform_Create( int x, int y, double angle, double scale )
{
    TW_Transform* transform = malloc( sizeof( TW_Transform ) );

    transform->position = TW_Vector2_Create( x, y );
    transform->centre = TW_Vector2_Create( 0, 0 );
    transform->angle = angle;
    transform->scale = scale;
    transform->flip = SDL_FLIP_NONE;
    transform->parent = NULL;

    return transform;
}


// Set the position of the transform.
void TW_Transform_SetPosition( TW_Transform* self, int x, int y )
{
    self->position->x = x;
    self->position->y = y;
}


// Frees the resources used by a TW_Transform object
void TW_Transform_Free( TW_Transform* self )
{
    self->scale = 0.0;
    self->angle = 0.0;
    TW_Vector2_Free( self->centre );
    TW_Vector2_Free( self->position );
    free( self );
}
