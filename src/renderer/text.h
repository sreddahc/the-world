#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "renderer.h"


// Type definitions

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
    TW_Texture renderedText;        // The TW_Texture. Rendered text is stored here
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
 * TW_Text_Init - Initialised a TW_Text object based on a series of parameters.
 * 
 * Args:
 * - TW_Text*       - self              - The TW_Text object to initialise
 * - char*          - textValue         - The value to assign to the TW_Text object
 * - char*          - fontName          - The name of the font to be used
 * - int            - fontSize          - The size of the font
 * - SDL_Color      - fontColour        - The colour of the font
 * 
 * Returns:
 * - bool           - true if successful, false if not
 */
bool TW_Text_Init( TW_Text* self, char* textValue, char* fontName, int fontSize, SDL_Color fontColour );


/**
 * TW_Text_FastInit - Creates a TW_Text object with only the text value as input.
 * Default is font DejaVuSans.ttf in size 16 black text.
 * 
 * Args:
 * - TW_Text*       - self              - The TW_Text object to initialise
 * - char*          - textValue         - The value to assign to the TW_Text object
 * 
 * Returns:
 * - bool           - true if successful, false if not
 */
bool TW_Text_FastInit( TW_Text* self, char* textValue );


/**
 * TW_Text_Render_Texture - Creates an SDL_Texture from a TW_Text object so that it can be
 * displayed (e.g. using LTexture_Render).
 * 
 * Args:
 * - TW_Text        - self              - The TW_Text object to render as a SDL_Texture
 * - SDL_Renderer*  - renderer          - The renderer that will be used to render the texture
 * 
 * Returns:
 * - bool           - true if successful, false if not
 */
bool TW_Text_Render_Texture( TW_Text* self, SDL_Renderer* renderer );
