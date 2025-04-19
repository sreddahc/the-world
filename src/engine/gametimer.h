#pragma once

#include <SDL2/SDL.h>

// Type definitions

#define MILLISECONDS_IN_A_SEC 1000.f
#define TIME_DELTA_CAP 10000
#define FPS_FRAME_CAP 200000


typedef struct TW_GameTimer {
    float delta_time;
    Uint64 now;
    Uint64 previous;
    Uint64 ms;
    Uint64 frame;
    int frameCap;
    int ticksPerFrame;
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
 * TW_GameTimer_GetTimeDelta - Get the current time delta between now and the last time
 *                             the game timer was updated.
 * 
 * Returns:
 * - float          - Time delta
 */
float TW_GameTimer_GetTimeDelta();


/**
 * TW_GameTimer_GetFPS - Get current Frames Per Second (FPS) as a float.
 * 
 * Returns:
 * - float          - Current FPS
 */
float TW_GameTimer_GetFPS();


/**
 * TW_GameTimer_SetFrameLimit - Given a Frame Per Second limit, limit the frame rate.
 * 
 * Args:
 * - int            - fps           - The FPS to be enforced. `0` = No limit.
 */
void TW_GameTimer_SetFrameLimit( int fps );


/**
 * TW_GameTimer_LimitFrameRate - If there is a frame cap set, delay the next frame to 
 *                               limit the frame rate.
 */
void TW_GameTimer_LimitFrameRate();


Uint64 TW_GameTimer_GetTime();


/**
 * TW_GameTimer_Free - Free resources used by the game timer.
 */
void TW_GameTimer_Free();