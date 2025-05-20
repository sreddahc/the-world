#pragma once

#include "../../engine/inputhandler.h"


// Type definitions

typedef struct TW_Scene TW_Scene;
typedef struct TW_Entity TW_Entity;
typedef struct TW_Component TW_Component;


/**
 * \brief The player object
 * 
 * \param parent `TW_Component*` – Parent component of the player object
 * \param jumping `bool` – Player jumping? `true` if so, `false` otherwise
 * \param falling `bool` – Player falling? `true` if so, `false` otherwise
 */
typedef struct TW_Player {
    TW_Component* parent;               // Parent component of the player object
    bool onGround;                      // Is the player on the ground?
    bool jumping;                       // Player jumping? `true` if so, `false` otherwise
    TW_Component* textureIdle;          // A pointer to the idling texture
    TW_Component* textureWalking;       // A pointer to the walking texture
} TW_Player;


// Function definitions

/**
 * \brief Creates a player component object.
 * 
 * \returns `TW_Player*` – The player object initialised
 */
TW_Player* TW_Player_Create();


/**
 * \brief Frees resources used by a player object.
 * 
 * \param self `TW_Player*` – The player object to free
 */
void TW_Player_Free( TW_Player* self );


/**
 * \brief The think function for the player entity.
 * 
 * \param component `TW_Entity*` – The entity the think function belongs to
 */
void TW_Player_Think( TW_Entity* entity );


/**
 * \brief Creates a player entity adds it to target scene.
 * 
 * \param target `TW_Scene*` – The target scene to add the player entity to
 * \param x `int` – Position of the player entity on the x axis
 * \param y `int` – Position of the player entity on the y axis
 */
void TW_Scene_GeneratePlayer( TW_Scene* target, int x, int y );


/**
 * \brief Check if player entity is on the ground
 * 
 * \param self `TW_Entity*` – The entity to check
 * 
 * \returns `bool` – `true` if entity on the ground. `false` otherwise
 */
bool TW_Player_OnGround( TW_Entity* self );
