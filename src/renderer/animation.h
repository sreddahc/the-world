#pragma once

#include <stdbool.h>
#include "renderer.h"

// Type definitions

/**
 * TW_Animation - An animated texture.
 * 
 * Elements:
 * - TW_Texture     - textureReel       - Texture with all animation components
 * - int            - height            - Height of the animation texture
 * - int            - width             - Width of the animation texture
 * - int            - frameCount        - Number of frames in the animation
 * - int            - currentFrame      - Current frame of the animation
 * - int            - animationSpeed    - Animation speed in milliseconds. Default = 100
 * - int            - timeLastUpdated   - Used to check when to update animation frames
 * - bool           - paused            - Pause animation? true = yes, false = no
 * - SDL_Rect*      - grid              - Grid that subdivides the texture based on the
 *                                        size of the animation object.
 * - TW_Texture     - texture           - Texture containing all frames of the animation           
 */
typedef struct TW_Animation {
    int width;
    int height;
    int frameCount;
    int currentFrame;
    int animationSpeed;
    int timeLastUpdated;
    bool paused;
    SDL_Rect* grid;
    TW_Texture texture;
} TW_Animation;


// Function definitions

/**
 * TW_Animation_Init - Initialises a TW_Animation object.
 * 
 * Args:
 * - TW_Animation*  - self              - The TW_Animation object to initialise
 * - char*          - path              - Path of the textureReel
 * - int            - height            - The height of the animation
 * - int            - width             - The width of the animation
 * - int            - frameCount        - The number of frames in the animation
 * - int            - animationSpeed    - Animation speed in milliseconds. Default = 100
 * - bool           - paused            - Is the animation paused? true = yes, false = no
 */
bool TW_Animation_Init( TW_Animation* self, SDL_Renderer* renderer, char* path, int height, int width, int frameCount, int animationSpeed, bool paused );


/**
 * TW_Animation_GetNextFrame - Gets the next frame texture in the animation and
 * increments the current frame counter.
 * 
 * Args:
 * - TW_Animation*  - self              - The TW_Animation object
 * 
 * Returns:
 * - bool           - true if no error, false otherwise
 */
void TW_Animation_GetNextFrame( TW_Animation* self );


/**
 * Fill this in!
 */
TW_Texture* TW_Animation_Get_Frame( TW_Animation* self );


/**
 * TW_Animation_Free - Frees resources used by a TW_Animation object.
 * 
 * Args:
 * - TW_Animation*  - self              - The TW_Animation object
 */
void TW_Animation_Free( TW_Animation* self );