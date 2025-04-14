#include "transform.h"

TW_Transform* TW_Transform_Create( int x, int y, float angle, float scale )
{
    TW_Transform* transform = malloc( sizeof( TW_Transform ) );

    transform->position = TW_Vector2_Create( x, y );
    transform->centre = TW_Vector2_Create( 0, 0 );
    transform->angle = angle;
    transform->scale = scale;
}


void TW_Transform_Free( TW_Transform* self )
{
    self->scale = 0.0;
    self->angle = 0.0;
    TW_Transform_Free( self->centre );
    TW_Transform_Free( self->position );
    free( self );
}