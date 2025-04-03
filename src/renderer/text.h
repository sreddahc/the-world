#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "renderer.h"

// TW_Text object
typedef struct TW_Text {
    char* textValue;            // Value of the TW_Text object
    char* fontName;             // Font of the TW_Text object. Default = DejaVuSerif.ttf
    int fontSize;               // Size of the TW_Text object. Default = 16
    SDL_Color fontColour;       // Colour of the TW_Text object Default = Black
    TTF_Font* fontObject;       // Font object for the TW_Text object
    LTexture* textTexture;      // The TW_Texture of the TW_Text object. Must be rendered before use
} TW_Text;


/**
 * TW_Text_SetFont - Sets to font of a TW_Text object.
 * 
 * Args:
 * TW_Text*     self            The TW_Text object to initialise
 * char*        fontName        The name of the font to be used
 * int          fontSize        The size of the font
 */
bool TW_Text_SetFont( TW_Text* self, char* fontName, int fontSize );


/**
 * TW_Text_Init - Initialised a TW_Text object based on a series of parameters.
 * 
 * Args:
 * TW_Text*     self            The TW_Text object to initialise
 * char*        textValue       The value to assign to the TW_Text object
 * char*        fontName        The name of the font to be used
 * int          fontSize        The size of the font
 * SDL_Color    fontColour      The colour of the font
 */
bool TW_Text_Init( TW_Text* self, char* textValue, char* fontName, int fontSize, SDL_Color fontColour );


/**
 * TW_Text_FastInit - Creates a TW_Text object with only the text value as input.
 * 
 * Args:
 * TW_Text*     self            The TW_Text object to initialise
 * char*        textValue       The value to assign to the TW_Text object
 * 
 * Will default to Black text in font size 16 of font face DejaVuSans.ttf
 */
bool TW_Text_FastInit( TW_Text* self, char* textValue );

