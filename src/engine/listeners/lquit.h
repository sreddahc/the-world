#pragma once

#include <stdbool.h>

// Type definitions

typedef struct TW_Listener TW_Listener;


typedef struct TW_L_Quit {
    bool quit;
} TW_L_Quit;


// Function definitions

TW_L_Quit* TW_L_Quit_Create();


void TW_L_Quit_Free( TW_L_Quit* self );
