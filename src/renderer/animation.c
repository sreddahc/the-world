#include "animation.h"
#include "../engine/timer.h"


// Initialises a TW_Animation object.
bool TW_Animation_Init( TW_Animation* self, SDL_Renderer* renderer, char* path, int height, int width, int frameCount, int animationSpeed, bool paused )
{
    self->width = width;
    self->height = height;
    self->frameCount = frameCount;
    self->currentFrame = 0;
    self->animationSpeed = animationSpeed;
    self->timeLastUpdated = 0;
    self->paused = paused;
    
    TW_Texture animationTexture;
    if( ! TW_Texture_LoadImage( &animationTexture, renderer, path ) )
    {
        return false;
    }
    self->texture = animationTexture;

    int gridCols = self->texture.width / width;
    int gridRows = self->texture.height / height;
    int gridSize = gridCols * gridRows;

    SDL_Rect* animationGrid = malloc( gridSize * sizeof( SDL_Rect ) );
    self->grid = animationGrid;
    for( int frame = 0; frame < gridSize; frame++ )
    {
        self->grid[ frame ].x = ( frame % gridCols ) * width;
        self->grid[ frame ].y = ( frame / gridCols ) * height;
        self->grid[ frame ].w = width;
        self->grid[ frame ].h = height;
    }

    return true;
}


// Gets the next frame texture in the animation and increments the current frame counter.
void TW_Animation_GetNextFrame( TW_Animation* self )
{
    if( ! self->paused )
    {
        // This is not the right way to implement DeltaTime... though it does work.
        if( SDL_GetTicks() - self->timeLastUpdated >= self->animationSpeed )
        {
            self->timeLastUpdated = SDL_GetTicks64();
            self->currentFrame = ( self->currentFrame + 1 ) % self->frameCount;
        }
    }
}


// Frees resources used by a TW_Animation object.
void TW_Animation_Free( TW_Animation* self )
{
    free( self->grid );
    self->grid = NULL;
    self->currentFrame = 0;
    self->frameCount = 0;
    self->width = 0;
    self->height = 0;
    TW_Texture_Free( &self->texture );
    self = NULL;
}
