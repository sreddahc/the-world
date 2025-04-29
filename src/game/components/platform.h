#pragma once


// Type definitions

typedef struct TW_Scene TW_Scene;
typedef struct TW_Component TW_Component;


enum TW_PlatformPosition {
    TW_PLATFORM_SINGLE,
    TW_PLATFORM_LEFT,
    TW_PLATFORM_MIDDLE,
    TW_PLATFORM_RIGHT,
    TW_PLATFORM_TOTAL
};


typedef struct TW_Platform {
    TW_Component* parent;
} TW_Platform;


// Function definitions

/**
 * TW_Platform_Create - Create a platform object.
 * 
 * Returns:
 * - TW_Platform*       - Platform object initialised
 */
TW_Platform* TW_Platform_Create();


/**
 * TW_Platform_Free - Free the resources used by a platform object.
 * 
 * Args:
 * - TW_Platform*       - self              - Platform object to free
 */
void TW_Platform_Free( TW_Platform* self );


/**
 * TW_Scene_GeneratePlatform - Create a platform entity at position x and y in target scene.
 * 
 * Args:
 * - TW_Scene*          - target            - Add the platform entity to this scene
 * - int                - x                 - The x position of the platform (anchor top-left)
 * - int                - y                 - The y position of the platform (anchor top-left)
 */
void TW_Scene_GeneratePlatform( TW_Scene* target, enum TW_PlatformPosition platformType, int x, int y );
