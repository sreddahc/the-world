#pragma once

#include "../ecs/scene.h"
#include "../renderer/text.h"
#include "../engine/gamestate.h"


// // Function definitions

void TW_DebugStats_FPS_Think();

/**
 * TW_DebugStats_Create - Generates a number of text objects with debug statistics.
 */
void TW_DebugStats_Create( TW_Scene* self );
