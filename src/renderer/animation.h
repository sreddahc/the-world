#pragma once

#include "sprite.h"


// Type definitions

typedef struct TW_Component TW_Component;


/**
 * TW_Animation - An animated texture.
 * 
 * Elements:
 * - TW_Sprite*     - sprites           - A sprite sheet with all frames of the animation
 * - int            - frameCount        - Number of frames in the animation
 * - int*           - animationFrames   - The frames which form the animation
 * - int            - currentFrame      - Current frame of the animation
 * - int            - animationSpeed    - Animation speed in milliseconds. Default = 100
 * - int            - timeLastUpdated   - Used to check when to update animation frames
 * - bool           - paused            - Pause animation? true = yes, false = no
 */
typedef struct TW_Animation {
    TW_Sprite* spriteSheet;     // The sprite object with all the texture information
    int frameCount;             // Number of frames in the animation
    int* animationFrames;       // Sprite frames that form part of the animation
    int currentFrame;           // The current frame of the animation
    int animationSpeed;         // Speed of the animation
    int timeLastUpdated;        // Time last updates (to determine next frame)
    bool paused;                // true = paused, false = unpaused
    TW_Component* parent        // Parent component if it exists, otherwise `NULL`
} TW_Animation;


// Function definitions

/**
 * TW_Animation_Create - Create an animation object from a sprite object
 * 
 * Args:
 * - TW_Sprite*         - spriteSheet       - The sprite sheet with all possible animation frames
 * - int                - framecount        - Number of frames in the animation
 * - int*               - animationFrames   - An array of frames that form the animation
 * 
 * Returns:
 * - TW_Animation*      - Animation object
 */
TW_Animation* TW_Animation_Create( TW_Sprite* spriteSheet, int frameCount, int* animationFrames );


/**
 * TW_Animation_Render - Renders current frame then increments to next frame if not paused
 * 
 * Args:
 * - TW_Animation*      - The animation object to render
 */
void TW_Animation_Render( TW_Animation* self );


/**
 * TW_Animation_Free - Frees resources used by a TW_Animation object.
 * 
 * Args:
 * - TW_Animation*      - self              - The TW_Animation object
 */
void TW_Animation_Free( TW_Animation* self );
