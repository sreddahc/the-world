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

/**
 * TW_GameTimer_Create - Create a game timer to be used globally by all objects.
 */
void TW_GameTimer_Create();


/**
 * TW_GameTimer_Update - Update the game timer.
 * This should be called once every cycle of the main loop.
 */
void TW_GameTimer_Update();


/**
 * TW_GameTimer_GetTimeDelta - Get the current time delta.
 */
float TW_GameTimer_GetTimeDelta();


/**
 * TW_GameTimer_Free - Free resources used by the game timer.
 */
void TW_GameTimer_Free();