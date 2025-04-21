#pragma once

#include "../ecs/scene.h"
#include "../engine/gamestate.h"
#include "../engine/maths.h"


// Function definitions


/**
 * TW_DebugStats_Mouse_Think - The think function for the mouse debug entity
 * 
 * Args:
 * - TW_Component*      - component         - The component the think function belongs to
 */
void TW_DebugStats_Mouse_Think( TW_Component* component );


/**
 * TW_DebugStats_FPS_Think - The think function for the FPS debug entity
 * 
 * Args:
 * - TW_Component*      - component         - The component the think function belongs to
 */
void TW_DebugStats_FPS_Think( TW_Component* component );


/**
 * TW_DebugStats_DeltaTime_Think - The think function for the delta time debug entity
 * 
 * Args:
 * - TW_Component*      - component         - The component the think function belongs to
 */
void TW_DebugStats_DeltaTime_Think( TW_Component* component );


/**
 * TW_DebugStats_Create - Generates a number of entities and adds them to a target scene
 *                        for the purposes of debugging
 * 
 * Args:
 * - TW_Scene*          - target            - The scene to add the debug stats to
 */
void TW_DebugStats_Create( TW_Scene* target );



/**
 * TW_DebugStats_Free - Free the resources used by a debug status object
 */
void TW_DebugStats_Free();
