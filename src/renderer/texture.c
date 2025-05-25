#include "texture.h"
#include "../engine/camera.h"
#include "../engine/maths.h"


// Create a colour object given a red, green and blue value
TW_Colour* TW_Colour_Create( int r, int g, int b, int a )
{
    TW_Colour* localColour = malloc( sizeof( TW_Colour ) );

    localColour->r = r;
    localColour->g = g;
    localColour->b = b;
    localColour->a = a;     

    return localColour;
}


// Get an SDL_Colour object from a TW_Colour object
SDL_Colour TW_Colour_Get( TW_Colour* self )
{
    SDL_Colour lColour = { self->r, self->g, self->b, self->a };
    return lColour;
}


// Free the resources used by a TW_Colour object
void TW_Colour_Free( TW_Colour* self )
{
    self->r = 0;
    self->g = 0;
    self->b = 0;
    self->a = 0;
    free( self );
}


// Creates a TW_Texture
TW_Texture* TW_Texture_CreateTexture()
{
    TW_Texture* texture = malloc( sizeof( TW_Texture ) );
    texture->hidden = false;
    texture->overlay = false;
    texture->parent = NULL;
    
    return texture;
}


// Create a TW_Texture from an SDL_Surface object.
bool TW_Texture_LoadSurface( TW_Texture* self, SDL_Surface* surface )
{
    bool success = true;

    self->width = surface->w;
    self->height = surface->h;

    SDL_Rect renderZone = { 0, 0, self->width, self->height };
    TW_Texture_Crop( self, renderZone );
    
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
void TW_Texture_Render( TW_Texture* self, TW_Transform* transform )
{
    // Render position
    TW_Vector2* position = TW_Vector2_Create( 0, 0 );
    TW_Vector2* offset = TW_Vector2_Create( 0, 0 );
    double angle = 0.0;
    double scale = 1.0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    if( transform != NULL )
    {
        position->x = transform->position->x;
        position->y = transform->position->y;
        angle = transform->angle;
        scale = transform->scale;
        flip = transform->flip;
        offset->x = transform->centre->x;
        offset->y = transform->centre->y;
    }

    int cameraOffsetX = 0;
    int cameraOffsetY = 0;
    if( self->overlay == false )
    {
        cameraOffsetX = TW_Camera_GetOffset( TW_AXIS_X );
        cameraOffsetY = TW_Camera_GetOffset( TW_AXIS_Y );
    }

    SDL_Rect renderZone = {
        position->x - offset->x - cameraOffsetX,
        position->y - offset->y - cameraOffsetY,
        (int)((double)self->crop.w * scale),
        (int)((double)self->crop.h * scale)
    };

    SDL_RenderCopyEx(
        TW_GetRenderer(),   // The renderer
        self->texture,      // The texture
        &self->crop,        // Source SDL_Rect (NULL for entire Texture)
        &renderZone,        // Destination SDL_Rect (NULL for entire rendering target)
        angle,              // Angle of the texture
        NULL,               // Axis centre point (NULL if centre of texture)
        flip                // Flip the texture
    );

    TW_Vector2_Free( offset );
    TW_Vector2_Free( position );
}


// Free resources used by a TW_Texture object.
void TW_Texture_Free( TW_Texture* self )
{
    if( self->texture != NULL )
    {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
        self->hidden = false;
        self->overlay = false;
        self->parent = NULL;
    }
    self->width = 0;
    self->height = 0;
    self->crop.x = 0;
    self->crop.y = 0;
    self->crop.w = 0;
    self->crop.h = 0;
    free( self );
}


//Crop a given TW_Texture object to the specified dimensions.
void TW_Texture_Crop(TW_Texture* self, SDL_Rect region )
{
    self->crop = region;
}
