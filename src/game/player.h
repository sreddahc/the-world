#pragma once

#include "../renderer/animation.h"

// Type definitions

typedef struct TW_Player {

    TW_Animation animation;

} TW_Player;


// Function definitions

void TW_Player_Create( TW_Player* self );
