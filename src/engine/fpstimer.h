#pragma once

#include <SDL2/SDL.h>


// Type definitions

#define MILLISECONDS_IN_A_SEC 1000.f
#define FRAME_CAP 200000


/**
 * TW_FPSTimer - A timer object responsible for keeping track of Frames Per Second (FPS).
 * 
 * Uint64       - ms        - Milliseconds since initialisation
 * Uint64       - frame     - Frames rendered since initialisation
 */
typedef struct TW_FPSTimer {
    Uint64 ms;      // Milliseconds
    Uint64 frame;   // Frames
} TW_FPSTimer;


// Function definitions

/**
 * TW_FPSTimer_Init - Initialises a TW_FPSTimer object.
 * 
 * Args:
 * TW_FPSTimer*     - self      - The TW_FPSTimer object to initialise
 */
void TW_FPSTimer_Init( TW_FPSTimer* self );


/**
 * TW_FPSTimer_Update - Updates a TW_FPSTimer object with the current frame count and
 * time. This must be done every frame to remain accurate.
 * 
 * Args:
 * TW_FPSTimer*     - self      - The TW_FPSTimer object to initialise
 */
void TW_FPSTimer_Update( TW_FPSTimer* self );


/**
 * TW_FPSTimer_GetFPS - Get the current number of Frames Per Second (FPS) as a float.
 * 
 * Args:
 * TW_FPSTimer*     - self      - The TW_FPSTimer object to initialise
 * 
 * Returns:
 * float            - The current FPS as a float
 */
float TW_FPSTimer_GetFPS( TW_FPSTimer* self );


/**
 * TW_FPSTimer_Free - Frees resources used by a TW_FPSTimer object.
 */
void TW_FPSTimer_Free( TW_FPSTimer* self );
