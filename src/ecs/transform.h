#pragma once

#include "../engine/maths.h"


// Type definitions

typedef struct TW_Component TW_Component;


/**
 * TW_Transform - A transform object used to provide basic information about an entity
 * 
 * Elements:
 * - TW_Coord*          - position      - The position of the entity on the x plane
 * - TW_Coord*          - centre        - The centre point of the entity. NULL defaults to { 0, 0 }
 * - float              - angle         - The angle of the entity (in degrees)
 * - float              - scale         - The scale of  the entity
 */
typedef struct TW_Transform {
    TW_Vector2* position;
    TW_Vector2* centre;
    double angle;
    double scale;
    TW_Component* parent                // Parent component if it exists, otherwise `NULL`
} TW_Transform;


// Function definitions

/**
 * TW_Transform_Create - Creates a TW_Transform object with the specified values
 * 
 * Args:
 * - TW_Vector2*        - position      - The position of the entity on the x plane
 * - TW_Vector2*        - centre        - The centre point of the entity. NULL defaults to { 0, 0 }
 * - float              - angle         - The angle of the entity (in degrees)
 * - float              - scale         - The scale of  the entity
 */
TW_Transform* TW_Transform_Create( int x, int y, double angle, double scale );


/**
 * TW_Transform_Free - Frees the resources used by a TW_Transform object
 * 
 * Args:
 * - TW_Transform*      - self          - The TW_Transform object to free
 */
void TW_Transform_Free( TW_Transform* self );