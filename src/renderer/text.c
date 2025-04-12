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
    TW_Text* textObject;

    textObject->textValue = textValue;
    textObject->fontColour = fontColour;

    if( ! TW_Text_SetFont( textObject, fontName, fontSize ) )
    {
        printf( "ERROR: TW_Text_Init - Failed to set font." );
    }

    return textObject;
}


TW_Text* TW_Text_FastCreate( char* textValue )
{
    char* fontName = "src/assets/fonts/dejavu/DejaVuSans.ttf";
    int fontSize = 16;
    SDL_Color fontColour = { 0, 0, 0 };

    TW_Text* textObject = TW_Text_Create( textValue, fontName, fontSize, fontColour );

    return textObject;
}


bool TW_Text_Render( TW_Text* self )
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( self->fontObject, self->textValue, self->fontColour );

    self->texture = TW_Texture_CreateTexture();
    self->texture->x = 50;
    self->texture->y = 50;
    TW_Texture_LoadSurface( self->texture, textSurface );

    SDL_FreeSurface( textSurface );

}

// bool TW_Text_Render_Texture( TW_Text* self, SDL_Renderer* renderer )
// {
//     bool success = true;

//     SDL_Surface* textSurface = TTF_RenderText_Solid( self->fontObject, self->textValue, self->fontColour );
//     if( textSurface == NULL )
//     {
//         printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
//         success = false;
//     }
//     else
//     {
//         self->renderedText.texture = SDL_CreateTextureFromSurface( renderer, textSurface );
//         if( self->renderedText.texture == NULL )
//         {
//             printf( "Unable to create texture from text. SDL Error: %s\n", SDL_GetError() );
//             success = false;
//         }
//         else
//         {
//             self->renderedText.width = textSurface->w;
//             self->renderedText.height = textSurface->h;
//         }
//         SDL_FreeSurface( textSurface );
//     }
    
//     return success;
// }
