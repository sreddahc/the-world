#include "maths.h"


// Creates an integer based vector of size 2
TW_Vector2* TW_Vector2_Create( int x, int y )
{
    TW_Vector2* vector = malloc( sizeof( TW_Vector2 ) );
    vector->x = x;
    vector->y = y;
    return vector;
}


// TW_Vector2_Set - Set the values of a vector2 object
void TW_Vector2_Set( TW_Vector2* self, int x, int y )
{
    self->x = x;
    self->y = y;
}


// Free resources used by a vector2 object
void TW_Vector2_Free( TW_Vector2* self )
{
    self->x = 0;
    self->y = 0;
    free( self );
}


// Creates a float based vector of size 2
TW_FVector2* TW_FVector2_Create( float x, float y )
{
    TW_FVector2* vector = malloc( sizeof( TW_FVector2 ) );
    vector->x = x;
    vector->y = y;
    return vector;
}


// Set the values of a fvector2 object
void TW_FVector2_Set( TW_FVector2* self, float x, float y )
{
    self->x = x;
    self->y = y;
}


// Free resources used by a fvector2 object
void TW_FVector2_Free( TW_FVector2* self )
{
    self->x = 0.0;
    self->y = 0.0;
    free( self );
}


// Given 2 points, find another point along that line.
int TW_Vector2_GetPoint( int x1, int y1, int x2, int y2, enum TW_Axis find, int point )
{
    float a = (float)( y2 - y1 ) / (float)( x2 - x1 );
    float b = (float)y1 - a * (float)x1;

    if( find == TW_AXIS_X )
    {
        return (int)( ( (float)point - b ) / a );
    }
    else
    {
        return (int)( (float)point * a + b );
    }
}
