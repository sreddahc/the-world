#pragma once

# include "../renderer/renderer.h"
# include "../renderer/text.h"
# include "../renderer/sprite.h"
# include "../renderer/animation.h"


// Type definitions

/**
 * TW_Component_Type - An enumeration of all the types of components so that they may be
 * uniquely identified.
 */
enum TW_Component_Type
{
    TW_COMPONENT_NODE,
    TW_COMPONENT_TEXTURE,
    TW_COMPONENT_TEXT,
    TW_COMPONENT_SPRITE,
    TW_COMPONENT_ANIMATION,
    TW_COMPONENT_TOTAL
};


/**
 * TW_Component_Value - A union of all valid component types. This union should have one
 * object matching each TW_Component_Type.
 */
typedef union TW_Component_Value {
    TW_Texture* texture;
    TW_Text* text;
    TW_Sprite* sprite;
    TW_Animation* animation;
} TW_Component_Value;


/**
 * TW_Component - Components are a part of entities to be added to TW_Entity objects
 * 
 * Args:
 * - int                    - type          - The type of component this is
 * - TW_Component_Value*    - value         - The component
 */
typedef struct TW_Component {
    int type;
    TW_Component_Value* value;
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
TW_Component* TW_Component_Create( int type, TW_Component_Value* value );


/**
 * TW_Component_Free - Frees resources for a given TW_Component
 */
void TW_Component_Free( TW_Component* self );