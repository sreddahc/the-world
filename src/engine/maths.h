#pragma once

#include <stdlib.h>
#include <stdbool.h>

// Type definitions

/**
 * \brief Describes an axis.
 */
enum TW_Axis {
    TW_AXIS_X,
    TW_AXIS_Y,
};


/**
 * \brief A representation of position using flags.
 */
enum TW_Direction {
    TW_DIR_UP = 0x1,
    TW_DIR_DOWN = 0x2,
    TW_DIR_LEFT = 0x4,
    TW_DIR_RIGHT = 0x8
};


/**
 * \brief Creates an integer based vector of size 2
 * 
 * \param x `int` – The x value
 * \param y `int` – The y value
 */
typedef struct TW_Vector2 {
    int x;
    int y;
} TW_Vector2;


/**
 * \brief Creates a float based vector of size 2
 * 
 * \param x `float` – The x value
 * \param y `float` – The y value
 */
typedef struct TW_FVector2 {
    float x;
    float y;
} TW_FVector2;


// Function definitions

/**
 * \brief Creates an integer based vector of size 2
 * 
 * Args:
 * \param x `int` – The x coordinate
 * \param y `int` – The y coordinate
 */
TW_Vector2* TW_Vector2_Create( int x, int y );

/**
 * \brief Set the values of a vector2 object
 * 
 * \param self `TW_Vector2*` – The vector2 object to update
 * \param x `int` – The x coordinate
 * \param y `int` – The y coordinate
 */
void TW_Vector2_Set( TW_Vector2* self, int x, int y );


/**
 * \brief Free resources used by a vector2 object
 * 
 * \param self `TW_Vector2*` – The vector2 object to update
 */
void TW_Vector2_Free( TW_Vector2* self );


/**
 * \brief Creates an integer based vector of size 2
 * 
 * \param x float – The x coordinate
 * \param y float – The y coordinate
 */
TW_FVector2* TW_FVector2_Create( float x, float y );

/**
 * \brief Set the values of a vector2 object
 * 
 * \param self `TW_FVector2*` – The vector2 object to update
 * \param x `float` – The x coordinate
 * \param y `float` – The y coordinate
 */
void TW_FVector2_Set( TW_FVector2* self, float x, float y );


/**
 * \brief Free resources used by a vector2 object
 * 
 * \param self `TW_FVector2*` – The vector2 object to update
 */
void TW_FVector2_Free( TW_FVector2* self );


/**
 * \brief Given 2 points, find another point along that line.
 * 
 * \param x1 `int` – X value for the first point
 * \param y1 `int` – Y value for the first point
 * \param x2 `int` – X value for the second point
 * \param y2 `int` – Y value for the second point
 * \param find `enum TW_Axis` – Axis to find (TW_AXIS_X or TW_AXIS_Y)
 * \param point `int` – position on axis opposite to the one that's being found
 * 
 * \returns `int` – Y if `point` is X or X if `point` is Y
 */
int TW_Vector2_GetPoint( int x1, int y1, int x2, int y2, enum TW_Axis find, int point );


// /**
//  * \brief Find the point furtherest in a direction for a given vector.
//  * 
//  * Direction
//  * Vector
//  * 
//  */
// int TW_Support( TW_Vector2* direction, TW_Vector2* vector );

/**
 * \brief Given 2 integers, return the larger of the 2
 * 
 * \param a `int`
 * \param b `int`
 * 
 * \returns `int` – The larger value between `a` and `b`. `a` if the same value.
 */
int TW_M_Max( int a, int b );


/**
 * \brief Given 2 integers, return the smaller of the 2
 * 
 * \param a `int`
 * \param b `int`
 * 
 * \returns `int` – The smaller value between `a` and `b`. `a` if the same value.
 */
int TW_M_Min( int a, int b );
