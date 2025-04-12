#include "texture.h"


// Creates a TW_Texture
TW_Texture* TW_Texture_CreateTexture()
{
    TW_Texture* texture = malloc( sizeof( TW_Texture ) );
    texture->angle = 0.0;
    texture->flip = SDL_FLIP_NONE;
    texture->x = 0;
    texture->y = 0;
    texture->useColourKey = false;
    SDL_Color colourKey = { 0x00, 0x00, 0x00, 0xff };
    texture->colourKey = colourKey;
    
    return texture;
}


// Create a TW_Texture from an SDL_Surface object.
bool TW_Texture_LoadSurface( TW_Texture* self, SDL_Surface* surface )
{
    bool success = true;

    self->renderWidth = surface->w;
    self->renderHeight = surface->h;
    self->textureWidth = surface->w;
    self->textureHeight = surface->h;

    TW_Texture_Crop( self, 0, 0, self->textureWidth, self->textureHeight );
    
    if( self->useColourKey == true )
    {
        SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, self->colourKey.r, self->colourKey.g, self->colourKey.b ) );
    }
    
    self->texture = SDL_CreateTextureFromSurface( TW_GetRenderer(), surface );
    if( self->texture == NULL )
    {
        printf( "Unable to create texture from surface. SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    return success;

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
        TW_Texture_LoadSurface( self, surface );
    }
    
    SDL_FreeSurface( surface );

    return success;
}


// Render a TW_Texture object.
void TW_Texture_Render( TW_Texture* self )
{
    SDL_Rect renderZone = { self->x, self->y, self->renderWidth, self->renderHeight };
    renderZone.w = self->crop.w + (self->textureWidth - self->crop.w);
    renderZone.h = self->crop.h + (self->textureHeight - self->crop.h);
    SDL_RenderCopyEx(
        TW_GetRenderer(),   // The renderer
        self->texture,      // The texture
        &self->crop,        // Source SDL_Rect (NULL for entire Texture)
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
        self->textureWidth = 0;
        self->textureHeight = 0;
        self->renderWidth = 0;
        self->renderHeight = 0;
        self->x = 0;
        self->y = 0;
        self->angle = 0.0;
        self->flip = 0;
        // This is likely not right... but likely not a big deal... maybe...
        SDL_Rect renderZone = { 0, 0, 0, 0 };
        self->crop = renderZone;
    }
}


//Crop a given TW_Texture object to the specified dimensions.
void TW_Texture_Crop(TW_Texture* self, int x, int y, int w, int h )
{
    SDL_Rect rectZone = { x, y, w, h }; 
    self->crop = rectZone;
}

// Sets the colour key of a TW_Texture object such that a given
void TW_Texture_SetColourKey( TW_Texture* self, int r, int g, int b )
{
    self->colourKey.r = r;
    self->colourKey.g = g;
    self->colourKey.b = b;
    self->useColourKey = true;
}
