#include "texture.h"


// Creates a TW_Texture
TW_Texture* TW_Texture_CreateTexture()
{
    TW_Texture* texture = malloc( sizeof( TW_Texture ) );
    texture->angle = 0.0;
    texture->flip = SDL_FLIP_NONE;
    texture->x = 0;
    texture->y = 0;
    return texture;
}


// Renders a image at a given path into a TW_Texture object.
bool TW_Texture_LoadImage( TW_Texture* self, char* path )
{
    bool success = true;

    SDL_Surface* surface = IMG_Load( path );
    if( surface == NULL )
    {
        printf( "Unable to load image %s. SDL_image error: %s\n", path, IMG_GetError() );
        success = false;
    }
    else
    {
        self->width = surface->w;
        self->height = surface->h;
    }

    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0x00, 0x00, 0x00 ) );

    self->texture = SDL_CreateTextureFromSurface( TW_GetRenderer(), surface );
    if( self->texture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        success = false;
    }
    
    SDL_FreeSurface( surface );

    return success;
}


// Render a TW_Texture object.
void TW_Texture_Render( TW_Texture* self )
{
    SDL_Rect renderZone = { self->x, self->y, self->width, self->height };
    if( ! self->crop == NULL )
    {
        renderZone.w = self->crop->w;
        renderZone.h = self->crop->h;
    }
    SDL_RenderCopyEx(
        TW_GetRenderer(),   // The renderer
        self->texture,      // The texture
        self->crop,         // Source SDL_Rect (NULL for entire Texture)
        &renderZone,        // Destination SDL_Rect (NULL for entire rendering target)
        self->angle,        // Angle of the texture
        NULL,               // Axis centre point (NULL if centre of texture)
        self->flip          // Flip the texture
    );
}


// Free resources used by a TW_Texture object.
void TW_Texture_Free( TW_Texture* self )
{
    if( self->texture != NULL )
    {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
        self->width = 0;
        self->height = 0;
        self->angle = 0.0;
        self->flip = 0;
        self->crop = NULL;
    }
}

SDL_Rect* TW_CreateSDLRect( int x, int y, int w, int h )
{
    SDL_Rect rectZone = { x, y, w, h };
    return &rectZone;
}

void TW_Texture_Crop(TW_Texture* self, int x, int y, int w, int h )
{
    self->crop = TW_CreateSDLRect( x, y, w, h );
}