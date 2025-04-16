#pragma once

// #include <stdbool.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "renderer.h"


// Type definitions

typedef struct TW_Component TW_Component;


/**
 * TW_Text - A wrapper object for rendering text to a TW_Texture object.
 * 
 * Elements:
 * - char*          - textValue         - Value of the text (i.e. the text itself)
 * - char*          - fontName          - Path to the font file to be used. Default = DejaVuSans.ttf
 * - int            - fontSize          - Size of the text in pt. Default = 16
 * - SDL_Color      - fontColour        - Colour of the font. Default = Black
 * - TTF_Font*      - fontObject        - The TTF_Font object required to render texture
 * - TW_Texture     - renderedText      - The TW_Texture. Rendered text is stored here
 */
typedef struct TW_Text {
    char* textValue;                // Value of the text (i.e. the text itself)
    char* fontName;                 // Path to the font file to be used.
    int fontSize;                   // Size of the text in pt. Default = 16
    SDL_Color fontColour;           // Colour of the font. Default = Black
    TTF_Font* fontObject;           // The TTF_Font object required to render the texture
    TW_Texture* texture;            // The TW_Texture. Rendered text is stored here
    TW_Component* parent;           // Parent component if it exists, otherwise `NULL`
} TW_Text;

// Function definitions

/**
 * TW_Text_SetFont - Sets to font of a TW_Text object.
 * 
 * Args:
 * - TW_Text*       - self              - The TW_Text object to initialise
 * - char*          - fontName          - The name of the font to be used
 * - int            - fontSize          - The size of the font
 * 
 * Returns:
 * - bool       - true if successful, false if not
 */
bool TW_Text_SetFont( TW_Text* self, char* fontName, int fontSize );


/**
 * TW_Text_Update - Updates a TW_Text texture to match TW_Text values
 * 
 * Args:
 * - TW_Text        - self              - The TW_Text object to render as a SDL_Texture
 */
bool TW_Text_Update( TW_Text* self );


/**
 * TW_Text_Create - Initialised a TW_Text object based on a series of parameters.
 * 
 * Args:
 * - char*          - textValue         - The value to assign to the TW_Text object
 * - char*          - fontName          - The name of the font to be used. `NULL` defaults to `DejaVuSans.ttf`
 * - int            - fontSize          - The size of the font. Font size `0` becomes `16`
 * - SDL_Color      - fontColour        - The colour of the font. `NULL` defaults to black
 * 
 * Returns:
 * - bool           - true if successful, false if not
 */
TW_Text* TW_Text_Create( char* textValue, char* fontName, int fontSize, TW_Colour* fontColour );


/**
 * TW_Text_Render - Renders a text object to the renderer
 */
void TW_Text_Render( TW_Text* self, TW_Transform* transform );


/**
 * TW_Text_Free - Frees resources used by a TW_Text object.
 * 
 * Args:
 * - TW_Text*       - self              - The TW_Text object to free resources from
 */
void TW_Text_Free( TW_Text* self );