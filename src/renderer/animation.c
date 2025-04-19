#include "animation.h"
#include "../engine/gametimer.h"

// Create an animation object from a sprite object
TW_Animation* TW_Animation_Create( TW_Sprite* spriteSheet, int frameCount, int* animationFrames )
{
    TW_Animation* animation = malloc( sizeof( TW_Animation ) );

    animation->spriteSheet = spriteSheet;
    animation->frameCount = frameCount;
    animation->animationFrames = animationFrames;
    animation->currentFrame = 0;
    animation->animationSpeed = 100;
    animation->timeSinceLastFrame = 0.0;
    animation->paused = false;

    // Checks
    for( int frame = 0; frame < frameCount; frame++ )
    {
        if( animation->animationFrames[ frame ] >= animation->spriteSheet->gridSize )
        {
            printf(
                "ERROR: Request for frame %d outside of range (grid size = %d)\n",
                animation->animationFrames[ frame ],
                animation->spriteSheet->gridSize
            );
            return NULL;
        }
    }

    animation->parent = NULL;

    return animation;
}


// Create an animation object from a sprite object
void TW_Animation_Render( TW_Animation* self, TW_Transform* transform )
{
    self->spriteSheet->currentSprite = self->animationFrames[ self->currentFrame ];
    TW_Sprite_Render( self->spriteSheet, transform );
    if( self->paused == false )
    {
        self->timeSinceLastFrame = self->timeSinceLastFrame + TW_GameTimer_GetTimeDelta();
        if( self->timeSinceLastFrame >= (float)self->animationSpeed / MILLISECONDS_IN_A_SEC )
        {
            self->timeSinceLastFrame = self->timeSinceLastFrame - (float)self->animationSpeed / MILLISECONDS_IN_A_SEC;
            self->currentFrame = ( self->currentFrame + 1 ) % self->frameCount;
        }
    }
}


// Frees resources used by a TW_Animation object.
void TW_Animation_Free( TW_Animation* self )
{
    self->paused = false;
    self->animationSpeed = 0;
    self->currentFrame = 0;
    for( int index = 0; index < self->frameCount; index++ )
    {
        self->animationFrames[ index ] = 0;
    }
    self->frameCount = 0;
    TW_Sprite_Free( self->spriteSheet );
    free( self );
}
