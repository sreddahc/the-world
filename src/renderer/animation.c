#include "animation.h"


// Initialises a TW_Animation object.
bool TW_Animation_Init( TW_Animation* self, SDL_Renderer* renderer, char* path, int height, int width, int frameCount, bool paused )
{
    bool success = true;

    self->width = width;
    self->height = height;
    self->frameCount = frameCount;
    self->currentFrame = 0;
    self->paused = paused;
    
    TW_Texture animationTexture;
    if( ! TW_Texture_LoadImage( &animationTexture, renderer, path ) )
    {
        success = false;
    }
    self->texture = animationTexture;

    int gridCols = self->texture.width / width;
    int gridRows = self->texture.height / height;
    int gridSize = gridCols * gridRows;

    // No idea if I'm doing memory allocation correctly... but should verify...
    SDL_Rect* animationGrid = malloc( gridSize * sizeof( *animationGrid ) );
    self->grid = animationGrid;
    for( int frame = 0; frame < gridSize; frame++ )
    {
        self->grid[ frame ].x = ( frame % gridCols ) * width;
        self->grid[ frame ].y = ( frame / gridCols ) * height;
        self->grid[ frame ].w = width;
        self->grid[ frame ].h = height;
    }

    return success;
}

void TW_Animation_GetNextFrame( TW_Animation* self )
{
    if( ! self->paused )
    {
        self->currentFrame = ( self->currentFrame + 1 ) % self->frameCount;
    }
}

void TW_Animation_Free( TW_Animation* self )
{
    // Need to verify to ensure that I'm doing memory freeing correctly...
    free( self->grid );
    self->grid = NULL;
    self->currentFrame = 0;
    self->frameCount = 0;
    self->width = 0;
    self->height = 0;
    TW_Texture_Free( &self->texture );
    self = NULL;
}
