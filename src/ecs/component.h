#pragma once

#include "think.h"
#include "components/transform.h"
#include "components/velocity.h"
#include "../renderer/renderer.h"
#include "../renderer/text.h"
#include "../renderer/sprite.h"
#include "../renderer/animation.h"


// Type definitions

// Placeholder for TW_Entity
typedef struct TW_Entity TW_Entity;

/**
 * TW_Component_Type - An enumeration of all the types of components so that they may be
 * uniquely identified.
 */
enum TW_ComponentType
{
    TW_C_TRANSFORM,
    TW_C_VELOCITY,
    TW_C_THINK,
    TW_C_TEXTURE,
    TW_C_TEXT,
    TW_C_SPRITE,
    TW_C_ANIMATION,
    TW_C_TOTAL
};


/**
 * TW_Component_Value - A union of all valid component types. This union should have one
 * object matching each TW_Component_Type.
 */
typedef union TW_ComponentValue {
    TW_Transform* transform;
    TW_Velocity* velocity;
    TW_Think* think;
    TW_Texture* texture;
    TW_Text* text;
    TW_Sprite* sprite;
    TW_Animation* animation;
} TW_ComponentValue;


/**
 * TW_Component - Components are a part of entities to be added to TW_Entity objects
 * 
 * Args:
 * - int                    - type          - The type of component this is
 * - TW_Component_Value*    - value         - The component
 */
typedef struct TW_Component {
    enum TW_ComponentType type;
    TW_Entity* parent;
    union {
        TW_Transform* transform;
        TW_Velocity* velocity;
        TW_Think* think;
        TW_Texture* texture;
        TW_Text* text;
        TW_Sprite* sprite;
        TW_Animation* animation;
    };
    // TW_Component_Value* value;
} TW_Component;


// Function definitions

/**
 * TW_Component_Create - Creates a pointer to a component of specified type and value.
 * 
 * Args:
 * - int                    - type          - The type of the component value
 * - TW_Component_Value*    - value         - A pointer to the component value
 * 
 * Returns:
 * - TW_Component*          - Returns a pointer to the component the specified type
 */
TW_Component* TW_Component_Create( int type, TW_ComponentValue* value );


/**
 * TW_Component_Render - If there is a visual aspect to the component... renders it
 * 
 * Args:
 * - TW_Component*          - self          - The TW_Component to render
 */
void TW_Component_Render( TW_Component* self, TW_Transform* transform );


/**
 * TW_Component_Run - Run logic components
 * 
 * Args:
 * - TW_Component*          - self          - The TW_Component to run
 */
void TW_Component_Run( TW_Component* self );


/**
 * TW_Component_GetParent - Given a component, return a pointer to its parent entity
 * object if it exists. If not, return `NULL`.
 * 
 * Args:
 * - TW_Component*          - self          - The component to fetch the parent entity of
 */
TW_Entity* TW_Component_GetParent( TW_Component* self );


/**
 * TW_Component_Free - Frees resources for a given TW_Component
 * 
 * Args:
 * - TW_Component*          - self          - The TW_Component to free
 */
void TW_Component_Free( TW_Component* self );