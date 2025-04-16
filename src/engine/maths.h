#pragma once

#include <stddef.h>
// #include <stdio.h>

// Type definitions

/**
 * TW_Vector2 - Creates a Vector of size 2
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
 * TW_Vector2_Create - Creates a TW_Coord object
 * 
 * Args:
 * - int            - x             - The x coordinate
 * - int            - y             - The y coordinate
 */
TW_Vector2* TW_Vector2_Create( int x, int y );

void TW_Vector2_Set( TW_Vector2* self, int x, int y );

void TW_Vector2_Free( TW_Vector2* self );