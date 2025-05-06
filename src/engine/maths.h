#pragma once

#include <stdlib.h>


// Type definitions

/**
 * TW_Axis - Describes an axis.
 * 
 * TW_AXIS_X = 0
 * TW_AXIS_Y = 1
 */
enum TW_Axis {
    TW_AXIS_X,
    TW_AXIS_Y,
};


/**
 * TW_Vector2 - Creates an integer based vector of size 2
 * 
 * Elements:
 * - int            - x                 - The x value
 * - int            - y                 - The y value
 */
typedef struct TW_Vector2 {
    int x;
    int y;
} TW_Vector2;


/**
 * TW_FVector2 - Creates a float based vector of size 2
 * 
 * Elements:
 * - float          - x                 - The x value
 * - float          - y                 - The y value
 */
typedef struct TW_FVector2 {
    float x;
    float y;
} TW_FVector2;


// Function definitions

/**
 * TW_Vector2_Create - Creates an integer based vector of size 2
 * 
 * Args:
 * - int            - x             - The x coordinate
 * - int            - y             - The y coordinate
 */
TW_Vector2* TW_Vector2_Create( int x, int y );

/**
 * TW_Vector2_Set - Set the values of a vector2 object
 * 
 * Args:
 * - TW_Vector2*    - self          - The vector2 object to update
 * - int            - x             - The x coordinate
 * - int            - y             - The y coordinate
 */
void TW_Vector2_Set( TW_Vector2* self, int x, int y );


/**
 * TW_Vector2_Free - Free resources used by a vector2 object
 * 
 * Args:
 * - TW_Vector2*    - self          - The vector2 object to update
 */
void TW_Vector2_Free( TW_Vector2* self );


/**
 * TW_FVector2_Create - Creates an integer based vector of size 2
 * 
 * Args:
 * - float          - x             - The x coordinate
 * - float          - y             - The y coordinate
 */
TW_FVector2* TW_FVector2_Create( float x, float y );

/**
 * TW_FVector2_Set - Set the values of a vector2 object
 * 
 * Args:
 * - TW_FVector2*   - self          - The vector2 object to update
 * - float          - x             - The x coordinate
 * - float          - y             - The y coordinate
 */
void TW_FVector2_Set( TW_FVector2* self, float x, float y );


/**
 * TW_FVector2_Free - Free resources used by a vector2 object
 * 
 * Args:
 * - TW_FVector2*   - self          - The vector2 object to update
 */
void TW_FVector2_Free( TW_FVector2* self );


// Given 2 vectors, work out the mid point given a y or x value.
/**
 * TW_Vector2_GetPoint - Given 2 points, find another point along that line.
 * 
 * Args:
 * - int            - x1            - X value for the first point
 * - int            - y1            - Y value for the first point
 * - int            - x2            - X value for the second point
 * - int            - y2            - Y value for the second point
 * - enum TW_Axis   - find          - Find this value (TW_AXIS_X or TW_AXIS_Y)
 * - int            - point         - Given point on other axis
 */
int TW_Vector2_GetPoint( int x1, int y1, int x2, int y2, enum TW_Axis find, int point );