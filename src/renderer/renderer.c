#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "renderer.h"


static SDL_Renderer* gRenderer = NULL;


void TW_CreateRenderer( SDL_Window* window, int index, Uint32 flags)
{
    gRenderer = SDL_CreateRenderer( window, index, flags );
}


SDL_Renderer* TW_GetRenderer()
{
    return gRenderer;
}


void TW_DestroyRenderer()
{
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
}

// ----------

// void TW_Texture_SetBlendMode( TW_Texture* self, SDL_BlendMode blending )
// {
//     SDL_SetTextureBlendMode( self->texture, blending );
// }


// void TW_Texture_SetColour( TW_Texture* self, Uint8 red, Uint8 green, Uint8 blue)
// {
//     SDL_SetTextureColorMod( self->texture, red, green, blue );
// }


// void TW_Texture_SetAlpha( struct TW_Texture* self, Uint8 alpha )
// {
//     SDL_SetTextureAlphaMod( self->texture, alpha );
// }


// int TW_Texture_GetWidth( TW_Texture* self )
// {
//     return self->width;
// }


// int TW_Texture_GetHeight( struct TW_Texture* self )
// {
//     return self->height;
// }


// void TW_Texture_Free( struct TW_Texture* self )
// {
//     if( self->texture != NULL )
//     {
//         SDL_DestroyTexture(self->texture);
//         self->texture = NULL;
//         self->width = 0;
//         self->height = 0;
//     }
// }