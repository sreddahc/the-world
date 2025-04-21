#pragma once

#include "../ecs/scene.h"
#include "../renderer/animation.h"
#include "../engine/inputhandler.h"


// Function definitions

/**
 * TW_Player_Think - The think function for the player entity
 * 
 * Args:
 * - TW_Component*      - component         - The component the think function belongs to
 */
void TW_Player_Think( TW_Component* component );


/**
 * TW_Player_Create - Creates a player entity and adds it to target scene
 * 
 * Args:
 * - TW_Scene*          - target            - The target scene to add the player entity to
 */
void TW_Player_Create( TW_Scene* target );
