#pragma once

#include "../../engine/inputhandler.h"


// Type definitions

typedef struct TW_Scene TW_Scene;
typedef struct TW_Entity TW_Entity;
typedef struct TW_Component TW_Component;


/**
 * TW_Player - The player object
 * 
 * Elements:
 * - TW_Component*      - parent        - Parent component of the player object
 * - bool               - jumping       - Player jumping? `true` if so, `false` otherwise
 * - bool               - falling       - Player falling? `true` if so, `false` otherwise
 */
typedef struct TW_Player {
    TW_Component* parent;               // Parent component of the player object
    bool jumping;                       // Player jumping? `true` if so, `false` otherwise
    bool falling;                       // Player falling? `true` if so, `false` otherwise
} TW_Player;


// Function definitions

/**
 * TW_Player_Create - Creates a player component object.
 * 
 * Returns:
 * - TW_Player*         - The player object initialised
 */
TW_Player* TW_Player_Create();


/**
 * TW_Player_Free - Frees resources used by a player object.
 * 
 * Args:
 * - TW_Player*         - self          - The player object to free
 */
void TW_Player_Free( TW_Player* self );


/**
 * TW_Player_Think - The think function for the player entity.
 * 
 * Args:
 * - TW_Component*      - component     - The component the think function belongs to
 */
void TW_Player_Think( TW_Entity* entity );


/**
 * TW_Scene_GeneratePlayer - Creates a player entity with all required components and adds
 *                           it to target scene.
 * 
 * Args:
 * - TW_Scene*          - target        - The target scene to add the player entity to
 * - int                - x             - Position of the player entity on the x axis
 * - int                - y             - Position of the player entity on the y axis
 */
void TW_Scene_GeneratePlayer( TW_Scene* target, int x, int y );
