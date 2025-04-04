#pragma once


/**
 * TW_Texture - A wrapper object that contains all information relating to a texture.
 * 
 * Elements:
 * SDL_Texture*   - texture   - SDL_Texture object
 * int            - width     - Width of the texture
 * int            - height    - Height of the texture
 */
typedef struct TW_Texture {
    SDL_Texture* texture;       // SDL_Texture object of a TW_Texture object
    int width;                  // Texture width
    int height;                 // Texture height
} TW_Texture;

// Function definitions

/**
 * TW_Texture_LoadImage - Renders a image at a given path into a TW_Texture object.
 * 
 * Args:
 * TW_Texture*    - self      - The TW_Texture object
 * SDL_Renderer*  - renderer  - The renderer that will render the image
 * char*          - path      - Path to the image to be rendered
 */
bool TW_Texture_LoadImage( TW_Texture* self, SDL_Renderer* renderer, char* path );


/**
 * TW_Texture_SetBlendMode - Set the blend mode that will be used in blending operations
 * 
 * Args:
 * TW_Texture*    - self      - The TW_Texture object
 * SDL_BlendMode  - blending  - The blend mode that will be set for blending operations
 */
void TW_Texture_SetBlendMode( TW_Texture* self, SDL_BlendMode blending );


/**
 * TW_Texture_SetColour - Sets the colour of a texture
 * 
 * Args:
 * TW_Texture*    - self      - The TW_Texture object
 * Uint8          - red       - Amount of Red to include in texture
 * Uint8          - green     - Amount of Green to include in texture
 * Uint8          - blue      - Amount of Blue to include in texture
 */
void TW_Texture_SetColour( TW_Texture* self, Uint8 red, Uint8 green, Uint8 blue);


/**
 * TW_Texture_SetAlpha - Sets the transparancy of a texture
 * 
 * Args:
 * TW_Texture*    - self      - The TW_Texture object
 * Uint8          - alpha     - Alpha: 0 = fully transparent to 255 = completely opaque
 */
void TW_Texture_SetAlpha( TW_Texture* self, Uint8 alpha );


/**
 * TW_Texture_Render - Render a given TW_Texture object
 * 
 * Args:
 * TW_Texture*        - self      - The TW_Texture object
 * SDL_Renderer*      - renderer  - The renderer that will render the image
 * int                - x         - The x position where the texture will be rendered
 * int                - y         - The y position where the texture will be rendered
 * SDL_Rect*          - clip      - Only show the part of the texture bound by the clip
 * double             - angle     - The angle (in degrees) to rotate the image
 * SDL_Point*         - centre    - Where the centre of the texture is. Default = middle
 * SDL_RendererFlip   - flip      - Flip the texture. SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL
 */
void TW_Texture_Render( TW_Texture* self, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip );


/**
 * TW_Texture_GetWidth - Given a TW_Texture, return the width of the texture
 * 
 * Args:
 * TW_Texture*        - self      - The TW_Texture object
 */
int TW_Texture_GetWidth( TW_Texture* self );


/**
 * TW_Texture_GetHeight - Given a TW_Texture, return the height of the texture
 * 
 * Args:
 * TW_Texture*        - self      - The TW_Texture object
 */
int TW_Texture_GetHeight( TW_Texture* self );


/**
 * TW_Texture_Free - Free a TW_Texture object
 * 
 * Args:
 * TW_Texture*        - self      - The TW_Texture object
 */
void TW_Texture_Free( TW_Texture* self );
