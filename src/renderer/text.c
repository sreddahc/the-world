#include "text.h"


bool TW_Text_SetFont( TW_Text* self, char* fontName, int fontSize )
{
    bool success = true;

    self->fontName = fontName;
    self->fontSize = fontSize;

    TTF_Font* fontObject = TTF_OpenFont( self->fontName, self->fontSize );
    if( fontObject == NULL )
    {
        printf( "ERROR: Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    self->fontObject = fontObject;

    return success;
}


bool TW_Text_Init( TW_Text* self, char* textValue, char* fontName, int fontSize, SDL_Color fontColour )
{
    bool success = true;

    self->textValue = textValue;
    self->fontColour = fontColour;

    if( ! TW_Text_SetFont( self, fontName, fontSize ) )
    {
        printf( "ERROR: TW_Text_Init - Failed to set font." );
        success = false;
    }

    return success;
}


bool TW_Text_FastInit( TW_Text* self, char* textValue )
{
    bool success = true;

    char* fontName = "src/assets/fonts/dejavu/DejaVuSans.ttf";
    int fontSize = 16;
    SDL_Color fontColour = { 0, 0, 0 };

    if( ! TW_Text_Init( self, textValue, fontName, fontSize, fontColour ) )
    {
        printf( "Failed to initialise TW_Text object." );
        success = false;
    }

    return success;
}


bool TW_Text_Render_Texture( TW_Text* self, SDL_Renderer* renderer )
{
    bool success = true;

    SDL_Surface* textSurface = TTF_RenderText_Solid( self->fontObject, self->textValue, self->fontColour );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        self->renderedText.texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( self->renderedText.texture == NULL )
        {
            printf( "Unable to create texture from text. SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            self->renderedText.width = textSurface->w;
            self->renderedText.height = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    
    return success;
}
