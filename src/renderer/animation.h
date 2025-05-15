#pragma once

#include "sprite.h"
#include "../engine/gamestate.h"


// Type definitions

#define MILLISECONDS_IN_A_SEC 1000.f

typedef struct TW_Component TW_Component;


/**
 * \brief An animated texture.
 * 
 * \param spriteSheet `TW_Sprite*` – The sprite object with all the texture information
 * \param animationSize `int` – Number of frames in the animation
 * \param animationFrames `int*` – Sprite frames that form part of the animation
 * \param currentFrame `int` – The current frame of the animation
 * \param animationSpeed `int` – Speed of the animation
 * \param timeSinceLastFrame `float` – Time since frame was last updated
 * \param paused `bool` – true = paused, false = unpaused
 * \param loop `bool` – `true` if animation loops, otherwise `false`
 * \param hidden `bool` – hide texture if `true`.
 * \param parent `TW_Component*` – Parent component if it exists, otherwise `NULL`
 */
typedef struct TW_Animation {
    TW_Sprite* spriteSheet;                 // The sprite object with all the texture information
    int animationSize;                      // Number of frames in the animation
    int* animationFrames;                   // Sprite frames that form part of the animation
    int currentFrame;                       // The current frame of the animation
    int animationSpeed;                     // Speed of the animation
    float timeSinceLastFrame;               // Time since frame was last updated
    bool paused;                            // true = paused, false = unpaused
    bool loop;                              // `true` if animation loops. default is `true`.
    bool hidden;                            // hide texture if `true`.
    TW_Component* parent;                   // Parent component if it exists, otherwise `NULL`
} TW_Animation;


// Function definitions

/**
 * \brief Create an animation object from a sprite object
 * 
 * \param spriteSheet `TW_Sprite*` – The sprite sheet with all possible animation frames
 * \param framecount `int` – Number of frames in the animation
 * \param animationFrames `int*` – An array of frames that form the animation
 * 
 * \returns `TW_Animation*` – Animation object
 */
TW_Animation* TW_Animation_Create( TW_Sprite* spriteSheet, int frameCount, int* animationFrames );


/**
 * \brief Frees resources used by a TW_Animation object.
 * 
 * \param self `TW_Animation*` – The TW_Animation object
 */
void TW_Animation_Free( TW_Animation* self );


/**
 * \brief Renders current frame then increments to next frame if not paused
 * 
 * \param self `TW_Animation*` – The animation object to render
 * \param transform `TW_Transform*` – Transform object for position, properties, etc...
 */
void TW_Animation_Render( TW_Animation* self, TW_Transform* transform );
