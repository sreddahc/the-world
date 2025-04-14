#include "maths.h"

TW_Vector2* TW_Vector2_Create( int x, int y )
{
    TW_Vector2* vector = malloc( sizeof( TW_Vector2 ) );
    vector->x = x;
    vector->y = y;
    return vector;
}


void TW_Vector2_Set( TW_Vector2* self, int x, int y )
{
    self->x = x;
    self->y = y;
}


void TW_Vector2_Free( TW_Vector2* self )
{
    self->x = 0;
    self->y = 0;
    free( self );
}