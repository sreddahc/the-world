#pragma once

#include "../ecs/scene.h"
#include "../renderer/animation.h"
#include "../engine/inputhandler.h"


// // Function definitions


void TW_Player_Think( TW_Component* component );


/**
 * TW_Player_Create - Creates a player entity... fill in the rest when time allows...
 */
TW_Entity* TW_Player_Create();
