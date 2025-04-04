#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "renderer.h"


bool TW_Texture_LoadImage( TW_Texture* self, SDL_Renderer* renderer, char* path ){
    
    bool success = true;
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
        success = false;
    }
    else
    {
        self->width = loadedSurface->w;
        self->height = loadedSurface->h;

        // Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0x00, 0xFF ) );
        
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
            success = false;
        }

        SDL_FreeSurface( loadedSurface );
    }

    self->texture = newTexture;

    return success;
}


void TW_Texture_SetBlendMode( TW_Texture* self, SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( self->texture, blending );
}


void TW_Texture_SetColour( TW_Texture* self, Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod( self->texture, red, green, blue );
}


void TW_Texture_SetAlpha( struct TW_Texture* self, Uint8 alpha )
{
    SDL_SetTextureAlphaMod( self->texture, alpha );
}


void TW_Texture_Render( TW_Texture* self, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip )
{
    // Set rendering space and render to screen
    SDL_Rect renderZone = { x, y, self->width, self->height };
    
    // Set clip dimensions
    if( clip != NULL )
    {
        renderZone.w = clip->w;
        renderZone.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx( renderer, self->texture, clip, &renderZone, angle, centre, flip );
}


int TW_Texture_GetWidth( TW_Texture* self )
{
    return self->width;
}


int TW_Texture_GetHeight( struct TW_Texture* self )
{
    return self->height;
}


void TW_Texture_Free( struct TW_Texture* self )
{
    if( self->texture != NULL )
    {
        SDL_DestroyTexture(self->texture);
        self->texture = NULL;
        self->width = 0;
        self->height = 0;
    }
}