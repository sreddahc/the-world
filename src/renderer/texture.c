#include "texture.h"
#include "../ecs/entity.h"


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
    texture->flip = SDL_FLIP_NONE;
    texture->parent = NULL;
    
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

    SDL_Rect renderZone = { 0, 0, self->textureWidth, self->textureHeight };
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
void TW_Texture_Render( TW_Texture* self )
{
    // Render position
    int x = 0;
    int y = 0;
    double angle = 0.0;

    if( self->parent != NULL )
    {
        TW_Component* transformComponent = TW_Entity_GetComponent( self->parent->parent, TW_COMPONENT_TRANSFORM );
        if ( transformComponent != NULL )
        {
            x = transformComponent->transform->position->x;
            y = transformComponent->transform->position->y;
            angle = transformComponent->transform->angle;
        }
    }

    SDL_Rect renderZone = { x, y, self->renderWidth, self->renderHeight };
    renderZone.w = self->crop.w + (self->renderWidth - self->crop.w);
    renderZone.h = self->crop.h + (self->renderHeight - self->crop.h);
    SDL_RenderCopyEx(
        TW_GetRenderer(),   // The renderer
        self->texture,      // The texture
        &self->crop,        // Source SDL_Rect (NULL for entire Texture)
        &renderZone,        // Destination SDL_Rect (NULL for entire rendering target)
        angle,        // Angle of the texture
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
        self->parent = NULL;
    }
    self->textureWidth = 0;
    self->textureHeight = 0;
    self->renderWidth = 0;
    self->renderHeight = 0;
    self->flip = 0;
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
