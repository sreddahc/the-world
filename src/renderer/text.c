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


TW_Text* TW_Text_Create( char* textValue, char* fontName, int fontSize, SDL_Color fontColour )
{
    TW_Text* textObject = malloc( sizeof( TW_Text ) );

    textObject->textValue = textValue;
    textObject->fontColour = fontColour;

    if( ! TW_Text_SetFont( textObject, fontName, fontSize ) )
    {
        printf( "ERROR: TW_Text_Init - Failed to set font." );
    }

    return textObject;
}


// Creates a TW_Text object with only the text value as input.
TW_Text* TW_Text_FastCreate( char* textValue )
{
    char* fontName = "src/assets/fonts/dejavu/DejaVuSans.ttf";
    int fontSize = 16;
    SDL_Color fontColour = { 0, 0, 0 };

    TW_Text* textObject = TW_Text_Create( textValue, fontName, fontSize, fontColour );

    return textObject;
}


// Creates an SDL_Texture from a TW_Text object so that it can be displayed later.
bool TW_Text_RenderTexture( TW_Text* self )
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( self->fontObject, self->textValue, self->fontColour );

    self->texture = TW_Texture_CreateTexture();
    TW_Texture_LoadSurface( self->texture, textSurface );
    SDL_FreeSurface( textSurface );
    TW_Texture_Render( self->texture );

}


// Frees resources used by a TW_Text object.
void TW_Text_Free( TW_Text* self )
{
    self->textValue = NULL;
    self->fontName = NULL;
    self->fontObject = NULL;
    self->fontColour.a = 0;
    self->fontColour.r = 0;
    self->fontColour.g = 0;
    self->fontColour.b = 0;
    self->fontSize = 0;
    TW_Texture_Free( self->texture );
    free( self );
}