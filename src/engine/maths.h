#pragma once

#include <stdlib.h>


// Type definitions

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