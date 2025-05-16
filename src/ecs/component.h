#pragma once

#include "components/collision.h"
#include "components/think.h"
#include "components/transform.h"
#include "components/velocity.h"
#include "../renderer/renderer.h"
#include "../renderer/text.h"
#include "../renderer/sprite.h"
#include "../renderer/animation.h"
#include "../game/components/platform.h"
#include "../game/components/player.h"
#include "../game/components/projectile.h"


// Type definitions

// Placeholder for TW_Entity
typedef struct TW_Entity TW_Entity;

/**
 * TW_Component_Type - An enumeration of all the types of components so that they may be
 * uniquely identified.
 */
enum TW_ComponentType {
    // Texture components
    TW_C_ANIMATION,
    TW_C_SPRITE,    
    TW_C_TEXTURE,
    TW_C_TEXT,
    // Logic components
    TW_C_COLLISION,
    TW_C_TRANSFORM,
    TW_C_THINK,
    TW_C_VELOCITY,
    // Game components
    TW_C_PLATFORM,
    TW_C_PLAYER,
    TW_C_PROJECTILE,
    // Metadata
    TW_C_TOTAL
};


/**
 * TW_Component - Components are a part of entities to be added to TW_Entity objects
 * 
 * Args:
 * - int                    - type          - The type of component this is
 * - bool                   - destroy       - Should this component be destroyed during clean up? `true` if so
 * - TW_Entity*             - parent        - Parent entity of this component
 * - TW_ComponentValue*     - value         - The component
 */
typedef struct TW_Component {
    enum TW_ComponentType type;
    bool destroy;
    TW_Entity* parent;
    union {
        // Texture components
        TW_Animation* animation;
        TW_Sprite* sprite;
        TW_Text* text;
        TW_Texture* texture;
        // Logic components
        TW_Collision* collision;
        TW_Think* think;
        TW_Transform* transform;
        TW_Velocity* velocity;
        // Game components
        TW_Platform* platform;
        TW_Player* player;
        TW_Projectile* projectile;
    };
} TW_Component;


// Function definitions

/**
 * TW_Component_Create - Creates a pointer to a component of specified type and value.
 * 
 * Args:
 * - int                    - type          - The type of the component value
 * - void*                  - value         - A pointer to the component value (TW_ComponentType)
 * 
 * Returns:
 * - TW_Component*          - Returns a pointer to the component the specified type
 */
TW_Component* TW_Component_Create( int type, void* value );


/**
 * TW_Component_GetParent - Given a component, return a pointer to its parent entity
 * object if it exists. If not, return `NULL`.
 * 
 * Args:
 * - TW_Component*          - self          - Get parent entity of this component.
 * 
 * Returns:
 * - TW_Entity*             - Parent entity if it exists. Otherwise return `NULL`.
 */
TW_Entity* TW_Component_GetParent( TW_Component* self );


/**
 * TW_Component_Free - Frees resources for a given TW_Component
 * 
 * Args:
 * - TW_Component*          - self          - The TW_Component to free
 */
void TW_Component_Free( TW_Component* self );


/**
 * TW_Component_Render - If there is a visual aspect to the component... render it
 * 
 * Args:
 * - TW_Component*          - self          - The TW_Component to render
 */
void TW_Component_Render( TW_Component* self, TW_Transform* transform );


/**
 * TW_Component_Run - Run logic components
 * 
 * Args:
 * - TW_Component*          - self          - The logic component to run
 */
void TW_Component_RunLogic( TW_Component* self );


/**
 * TW_Component_RunPhysics - Run physics components
 * 
 * Args:
 * - TW_Component*          - self          - The physics component to run
 */
void TW_Component_RunPhysics( TW_Component* self );


/**
 * TW_Component_Clear - Clear the state of state-based components so they're ready to be
 *                      used in the next game loop.
 * 
 * Args:
 * - TW_Component*          - self          - The component to clear
 */
void TW_Component_Clear( TW_Component* self );
