#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

// Type definitions

/**
 * TW_Timer - A struct for a timer object to keep track of time.
 * 
 * Elements:
 * Uint64       - currentTime       - Time the clock was created in milliseconds
 * bool         - paused            - Is the timer paused? True = paused, false = unpaused. Default = false
 * Uint64       - pauseTime         - Time the clock was paused, only used while paused. Default = 0
 * Uint64       - pauseDuration     - How long has the timer been paused for? Default = 0
 */
typedef struct TW_Timer {
    Uint64 currentTime;     // Time the clock was created in milliseconds
    bool paused;            // Is the timer paused? true = yes, false = no. Default = false
    Uint64 pauseTime;       // Time the clock was paused in milliseconds
    Uint64 pauseDuration;   // How long has the timer been paused for? Default = 0
} TW_Timer;


// Function definitions

/**
 * TW_Timer_Init - Initialises a TW_Timer object.
 * 
 * Args:
 * TW_Timer*      - self          - The TW_Timer object
 * bool           - paused        - True = paused, False = unpaused
 */
void TW_Timer_Init( TW_Timer* self, bool paused );


TW_Timer* TW_Timer_Create( bool paused );

/**
 * TW_Timer_Reset - Resets a TW_Timer object without changing the state.
 * 
 * Args:
 * TW_Timer*      - self          - The TW_Timer object
 */
void TW_Timer_Reset( TW_Timer* self );


/**
 * TW_Timer_Pause - Pause an unpaused TW_Timer object.
 * 
 * Args:
 * TW_Timer*      - self          - The TW_Timer object
 */
void TW_Timer_Pause( TW_Timer* self );


/**
 * TW_Timer_Resume - Resume a paused TW_Timer object.
 * 
 * Args:
 * TW_Timer*      - self          - The TW_Timer object
 */
void TW_Timer_Resume( TW_Timer* self );


/**
 * TW_Timer_GetTime - Resumes a TW_Timer object.
 * 
 * Args:
 * TW_Timer*      - self          - The TW_Timer object
 * 
 * Returns:
 * Uint64         - Current time of the TW_Timer object
 */
Uint64 TW_Timer_GetTime( TW_Timer* self );


/**
 * TW_Timer_Free - Frees the memory of a TW_Timer object.
 */
void TW_Timer_Free( TW_Timer* self );