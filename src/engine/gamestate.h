#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

// Type definitions

#define MILLISECONDS_IN_A_SEC 1000.f
#define TIME_DELTA_CAP 2000
#define FPS_FRAME_CAP 200000


typedef struct TW_GameState {
    float deltaTime;
    Uint64 now;
    Uint64 previous;
    Uint64 ms;
    Uint64 frame;
    int frameCap;
    int ticksPerFrame;
    bool paused;
} TW_GameState;

// Function definitions

/**
 * TW_GameTimer_Create - Create a game timer to be used globally by all objects.
 */
void TW_GameState_Create();


/**
 * TW_GameTimer_Update - Update the game timer.
 * This should be called once every cycle of the main loop.
 */
void TW_GameState_Update();


/**
 * TW_GameState_GetDeltaTime - Get the current time delta between now and the last time
 *                             the game timer was updated.
 * 
 * Returns:
 * - float          - Time delta
 */
float TW_GameState_GetDeltaTime();


/**
 * TW_GameTimer_GetFPS - Get current Frames Per Second (FPS) as a float.
 * 
 * Returns:
 * - float          - Current FPS
 */
float TW_GameState_GetFPS();


/**
 * TW_GameTimer_SetFrameLimit - Given a Frame Per Second limit, limit the frame rate.
 * 
 * Args:
 * - int            - fps           - The FPS to be enforced. `0` = No limit.
 */
void TW_GameState_SetFrameLimit( int fps );


/**
 * TW_GameTimer_LimitFrameRate - If there is a frame cap set, delay the next frame to 
 *                               limit the frame rate.
 */
void TW_GameState_LimitFrameRate();


/**
 * TW_GameState_GetTime - Get the current time in ms.
 * 
 * Returns:
 * - Uint64         - The current time in ms.
 */
Uint64 TW_GameState_GetTime();


/**
 * TW_GameState_PauseStatus - Get the current pause status of the game.
 * 
 * Returns:
 * - bool           - true if paused, false if not
 */
bool TW_GameState_PauseStatus();


/**
 * TW_GameState_Pause - Pause the game.
 */
void TW_GameState_Pause();


/**
 * TW_GameState_Resume - Unpause/resume the game.
 */
void TW_GameState_Resume();


/**
 * TW_GameTimer_Free - Free resources used by the game timer.
 */
void TW_GameState_Free();