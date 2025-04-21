#include "text.h"

#define DEFAULT_FONT "src/assets/fonts/dejavu/DejaVuSans.ttf"


// Sets to font of a TW_Text object
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


// Updates a TW_Text texture to match TW_Text values
bool TW_Text_Update( TW_Text* self )
{
    SDL_Surface* textSurface = TTF_RenderText_Blended( self->fontObject, self->textValue, self->fontColour );
    
    // -- BEGIN: Refactor - Fixes a memory leak... but free perhaps shouldn't be here.
    if( self->texture != NULL )
    {
        TW_Texture_Free( self->texture );
    }
    self->texture = TW_Texture_CreateTexture();
    // -- END: Refactor - Instead might be better to update the existing texture rather
    //                    than make a new one.

    TW_Texture_LoadSurface( self->texture, textSurface );
    SDL_FreeSurface( textSurface );
}


// Initialise a TW_Text object based on a series of parameters
TW_Text* TW_Text_Create( char* textValue, char* fontName, int fontSize, TW_Colour* fontColour )
{
    TW_Text* textObject = malloc( sizeof( TW_Text ) );
    textObject->texture = NULL;

    // Set defaults where applicable
    if( fontColour == NULL )
    {
        fontColour = TW_Colour_Create( 0x00, 0x00, 0x00, 0xff );
    }
    textObject->textValue = textValue;
    textObject->fontColour = TW_Colour_Get( fontColour );
    TW_Colour_Free( fontColour );

    // Font size
    if( fontSize == 0 )
    {
        fontSize = 16;
    }

    // Font face
    if( fontName == NULL )
    {
        fontName = DEFAULT_FONT;
    }

    if( ! TW_Text_SetFont( textObject, fontName, fontSize ) )
    {
        printf( "ERROR: Failed to set font\n" );
    }

    TW_Text_Update( textObject );

    textObject->parent = NULL;

    return textObject;
}


// Renders a text object to the renderer
void TW_Text_Render( TW_Text* self, TW_Transform* transform )
{
    TW_Texture_Render( self->texture, transform );
}


// Frees resources used by a TW_Text object
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