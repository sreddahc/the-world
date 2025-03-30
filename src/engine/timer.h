#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

// Type definitions

// TW_Timer object
typedef struct TW_Timer {
    Uint64 currentTime;     // Time the clock was created in milliseconds.
    bool paused;            // Is the timer paused - true = yes, false = no. Default = false
    Uint64 pauseTime;       // Time the clock was paused in milliseconds.
    Uint64 pauseDuration;   // How long has the timer been paused for? Default = 0
} TW_Timer;

// Function definitions

void TW_Timer_Init( TW_Timer* self, bool paused );
void TW_Timer_Reset( TW_Timer* self );
void TW_Timer_Pause( TW_Timer* self );
void TW_Timer_Resume( TW_Timer* self );
Uint64 TW_Timer_GetTime( TW_Timer* self );