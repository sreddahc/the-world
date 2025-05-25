#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

// Type definitions

#define MILLISECONDS_IN_A_SEC 1000.f
#define TIME_DELTA_CAP 2000
#define FPS_FRAME_CAP 200000
// #define SCREEN_WIDTH = 1280;
// #define SCREEN_HEIGHT = 768;


typedef struct TW_Vector2 TW_Vector2;
typedef struct TW_Level TW_Level;


typedef struct TW_GameState {
    float deltaTime;
    Uint64 now;
    Uint64 previous;
    Uint64 ms;
    Uint64 frame;
    int frameCap;
    int ticksPerFrame;
    bool paused;
    TW_Vector2* screenSize;
    TW_Level* level;
} TW_GameState;


// Function definitions

/**
 * \brief Create a game timer to be used globally by all objects.
 */
void TW_GameState_Create();


/**
 * \brief Free resources used by the game timer.
 */
void TW_GameState_Free();


/**
 * \brief Update the game timer. This should be called once every cycle of the main loop.
 */
void TW_GameState_Update();


/**
 * \brief The current time delta between now and the last time the game timer was updated.
 * 
 * Returns:
 * \returns `float` – Time delta
 */
float TW_GameState_GetDeltaTime();


/**
 * \brief Get current Frames Per Second (FPS) as a float.
 * 
 * \returns `float` – Current FPS
 */
float TW_GameState_GetFPS();


/**
 * \brief Given a Frame Per Second limit, limit the frame rate.
 * 
 * \param fps `int` – The FPS to be enforced. `0` = No limit.
 */
void TW_GameState_SetFrameLimit( int fps );


/**
 * \brief If there is a frame cap set, delay the next frame to  limit the frame rate.
 */
void TW_GameState_LimitFrameRate();


/**
 * \brief Get the current time in ms.
 * 
 * \returns `Uint64` – The current time in ms.
 */
Uint64 TW_GameState_GetTime();


/**
 * \brief Get the current pause status of the game.
 * 
 * \returns `bool` – true if paused, false if not
 */
bool TW_GameState_PauseStatus();


/**
 * \brief Pause the game.
 */
void TW_GameState_Pause();


/**
 * \brief Unpause/resume the game.
 */
void TW_GameState_Resume();


/**
 * \brief Get the current screen size.
 * 
 * \returns `TW_Vector2*` – pointer to the screen size.
 */
TW_Vector2* TW_GameState_GetScreenSize();


/**
 * \brief Set the current level.
 * 
 * \param level `TW_Level*` – The current level.
 */
void TW_GameState_SetLevel( TW_Level* level );


/**
 * \brief Get the current level.
 * 
 * \returns `TW_Level*` – The current level.
 */
TW_Level* TW_GameState_GetLevel();