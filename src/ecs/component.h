#pragma once

#include "../renderer/animation.h"

// Type definitions


enum TW_Component_Type
{
    TW_COMPONENT_NODE,
    TW_COMPONENT_ANIMATION,
    TW_COMPONENT_TOTAL_COMPONENTS
};


/**
 * TW_Component - Components are a part of entities to be added to TW_Entity objects
 * 
 * Args:
 * - int            - type          - The type of component this is
 * - union          - component     - The data component of the matching type
 */
typedef struct TW_Component {
    int type;
    union {
        TW_Animation animation;
    } component;
} TW_Component;