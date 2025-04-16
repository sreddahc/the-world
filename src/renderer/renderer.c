#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "renderer.h"


static SDL_Renderer* gRenderer = NULL;


// Create the renderer
void TW_CreateRenderer( SDL_Window* window, int index, Uint32 flags)
{
    gRenderer = SDL_CreateRenderer( window, index, flags );
}


// Get the renderer
SDL_Renderer* TW_GetRenderer()
{
    return gRenderer;
}


// Destroy the renderer
void TW_DestroyRenderer()
{
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
}
