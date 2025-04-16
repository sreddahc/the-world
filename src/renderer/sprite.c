#include "sprite.h"


// Create a sprite from a sprite sheet from a given path
TW_Sprite* TW_Sprite_Create( char* path, int width, int height )
{
    TW_Sprite* sprite = malloc( sizeof( TW_Sprite ) );

    sprite->width = width;
    sprite->height = height;

    sprite->texture = TW_Texture_CreateTexture();
    TW_Texture_LoadImage( sprite->texture, path );
    // sprite->texture->width = sprite->width;
    // sprite->texture->height = sprite->height;

    int rows = sprite->texture->height / sprite->height;
    int cols = sprite->texture->width / sprite->width;
    sprite->gridSize = rows * cols;
    
    SDL_Rect* grid = malloc( sprite->gridSize * sizeof( SDL_Rect ) );
    sprite->grid = grid;
    for( int frame = 0; frame < sprite->gridSize; frame++ )
    {
        sprite->grid[ frame ].x = ( frame % cols ) * sprite->width;
        sprite->grid[ frame ].y = ( frame / cols ) * sprite->height;
        sprite->grid[ frame ].w = sprite->width;
        sprite->grid[ frame ].h = sprite->height;
    }
    
    sprite->currentSprite = 0;
    sprite->parent = NULL;

    return sprite;
}


// Free the resources used by a sprite object
void TW_Sprite_Free( TW_Sprite* self )
{
    self->currentSprite = 0;
    for( int frame = 0; frame < self->gridSize; frame++ )
    {
        self->grid[ frame ].x = 0;
        self->grid[ frame ].y = 0;
        self->grid[ frame ].w = 0;
        self->grid[ frame ].h = 0;
    }
    free(self->grid);
    self->gridSize = 0;
    TW_Texture_Free( self->texture );
    self->height = 0;
    self->width = 0;
    free( self );
}

// Select a sprite from a TW_Sprite sprite sheet
void TW_Sprite_Render( TW_Sprite* self, TW_Transform* transform )
{
    TW_Texture_Crop( self->texture, self->grid[ self->currentSprite ] );
    TW_Texture_Render( self->texture , transform );
}
