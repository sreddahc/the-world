#pragma once

#include "../ecs/scene.h"
#include "../renderer/text.h"
#include "../engine/gamestate.h"
#include "../engine/maths.h"


// // Function definitions

void TW_DebugStats_Mouse_Think( TW_Component* component );

void TW_DebugStats_FPS_Think( TW_Component* component );

void TW_DebugStats_DeltaTime_Think( TW_Component* component );

/**
 * TW_DebugStats_Create - Generates a number of text objects with debug statistics.
 */
void TW_DebugStats_Create( TW_Scene* self );

void TW_DebugStats_Free();
