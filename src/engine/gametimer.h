#pragma once

#include <SDL2/SDL.h>

// Type definitions

#define TIME_DELTA_CAP 10000


typedef struct TW_GameTimer {
    float delta_time;
    Uint64 now;
    Uint64 previous;
} TW_GameTimer;

// Function definitions

void TW_GameTimer_Create();

void TW_GameTimer_Update();

float TW_GameTimer_GetTimeDelta();

void TW_GameTimer_Free();