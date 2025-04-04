#pragma once

// Type definitions
typedef struct LTexture {
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
} LTexture;

// Type definitions
typedef struct TW_Texture {
    SDL_Texture* texture;       // SDL_Texture object of a TW_Texture object
    int width;                  // Texture width
    int height;                 // Texture height
} TW_Texture;

// Function definitions

bool TW_Texture_LoadImage( TW_Texture* self, SDL_Renderer* renderer, char* path );
bool TW_Texture_LoadText( LTexture* self, SDL_Renderer* renderer, char* textValue, TTF_Font* font, SDL_Color textColour );
void TW_Texture_SetBlendMode( TW_Texture* self, SDL_BlendMode blending );
void TW_Texture_SetColour( TW_Texture* self, Uint8 red, Uint8 green, Uint8 blue);
void TW_Texture_SetAlpha( struct TW_Texture* self, Uint8 alpha );
void TW_Texture_Render( TW_Texture* self, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip );
int TW_Texture_GetWidth( TW_Texture* self );
int TW_Texture_GetHeight( struct TW_Texture* self );
void TW_Texture_Free( TW_Texture* self );

bool LTexture_LoadImage( LTexture* self, SDL_Renderer* renderer, char* path );
bool LTexture_LoadText( LTexture* self, SDL_Renderer* renderer, char* textValue, TTF_Font* font, SDL_Color textColour );
void LTexture_SetBlendMode( LTexture* self, SDL_BlendMode blending );
void LTexture_SetColour( LTexture* self, Uint8 red, Uint8 green, Uint8 blue);
void LTexture_SetAlpha( LTexture* self, Uint8 alpha );
void LTexture_Render( LTexture* self, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip );
int LTexture_GetWidth( LTexture* self );
int LTexture_GetHeight( LTexture* self );
void LTexture_Free( LTexture* self );
