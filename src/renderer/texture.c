#include "texture.h"


// Creates a TW_Texture
TW_Texture* TW_Texture_CreateTexture()
{
    TW_Texture* texture = malloc( sizeof( TW_Texture ) );
    texture->angle = 0.0;
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
        SDL_Rect renderZone = { 0, 0, self->width, self->height };
        self->crop = &renderZone;
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
    SDL_RenderCopyEx(
        TW_GetRenderer(),   // The renderer
        self->texture,      // The texture
        NULL,               // Source SDL_Rect (NULL for entire Texture)
        NULL,               // Destination SDL_Rect (NULL for entire rendering target)
        0.0,                // Angle
        NULL,               // Axis centre point (NULL if centre of texture)
        SDL_FLIP_NONE
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
        self->crop = NULL;
    }
}
