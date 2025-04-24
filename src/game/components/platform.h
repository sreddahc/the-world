#pragma once

#include "../../ecs/scene.h"
#include "../../renderer/sprite.h"


// Type definitions

enum TW_PlatformPosition {
    TW_PLATFORM_LEFT,
    TW_PLATFORM_MIDDLE,
    TW_PLATFORM_RIGHT
};


typedef struct TW_Platform {
} TW_Platform;


// Function definitions

/**
 * TW_Platform_Create - Create a platform entity at position x and y in target scene.
 * 
 * Args:
 * - TW_Scene*          - target            - Add the platform entity to this scene
 * - int                - x                 - The x position of the platform (anchor top-left)
 * - int                - y                 - The y position of the platform (anchor top-left)
 */
void TW_Platform_Create( TW_Scene* target, enum TW_PlatformPosition platformType, int x, int y );


void TW_Platform_Free( TW_Platform* self );