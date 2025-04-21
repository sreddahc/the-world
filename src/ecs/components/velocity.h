#pragma once

#include "transform.h"
#include "../../engine/gamestate.h"
#include "../../engine/maths.h"


// Type definitions

#define MILLISECONDS_IN_A_SEC 1000.f

typedef struct TW_Component TW_Component;
typedef struct TW_Transform TW_Transform;


/**
 * TW_Velocity - Records the velocity of an entity. Pairs with a transform entity.
 */
typedef struct TW_Velocity {
    TW_Vector2* speed;                  // Pixels to be traversed per interval in the x and y coords
    TW_Vector2* acceleration;           // Increase/decrease of speed per interval for the x and y coords
    int interval;                       // Check speed and acceleration every interval ms. Default: `100` ms
    float timeSinceLastInterval;        // The time since the last interval (based on delta time)
    TW_Component* parent;               // The parent component of this object. `NULL` if it doesn't exist
} TW_Velocity;


// Function definitons

/**
 * TW_Velocity_Create - Create a TW_Velocity object with speed and acceleration.
 *                      Interacts with a TW_Transform object.
 * 
 * Args:
 * - int                - xS            - The speed along the x coord in pixels per interval
 * - int                - yS            - The speed along the y coord in pixels per interval
 * - int                - xA            - The acceleration along the x coord in pixels per interval
 * - int                - yA            - The acceleration along the y coord in pixels per interval
 */
TW_Velocity* TW_Velocity_Create( int xS, int yS, int xA, int yA );


/**
 * TW_Velocity_SetSpeed - Change the speed of a velocity object
 * 
 * Args:
 * - TW_Velocity*       - self          - The velocity object to update
 * - int                - x             - New speed in x direction
 * - int                - y             - New speed in y direction
 */
void TW_Velocity_SetSpeed( TW_Velocity* self, int x, int y );


/**
 * TW_Velocity_SetAcceleration - Change the acceleration of a velocity object
 * 
 * Args:
 * - TW_Velocity*       - self          - The velocity object to update
 * - int                - x             - New acceleration in x direction
 * - int                - y             - New acceleration in y direction
 */
void TW_Velocity_SetAcceleration( TW_Velocity* self, int x, int y );


/**
 * TW_Velocity_SetInterval - Set the interval of a velocity object
 * 
 * Args:
 * - TW_Velocity*       - self          - The velocity object to update
 * - int                - interval      - New interval in ms for the velocity object
 */
void TW_Velocity_SetInterval( TW_Velocity* self, int interval );


/**
 * TW_Velocity_Run - Run the velocity object. This should be done every loop as long as the
 *                   game is not paused.
 * 
 * Args:
 * - TW_Velocity*       - self          - The velocity object to run
 * - TW_Component*      - transform     - The transform object to operate on
 */
void TW_Velocity_Run( TW_Velocity* self, TW_Transform* transform );


/**
 * TW_Velocity_Free - Frees the resources used by a velocity object
 * 
 * Args:
 * - TW_Velocity*       - self          - The velocity object to free
 */
void TW_Velocity_Free( TW_Velocity* self );