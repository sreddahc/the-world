#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "renderer/renderer.h"
#include "renderer/text.h"
#include "engine/timer.h"
#include "engine/fpstimer.h"

// Global variables
// Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

// Key press surface constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
// TTF_Font* gFontTitle = NULL;
TTF_Font* gFontNormal = NULL;

typedef struct MousePosition {
    int x;
    int y;
} MousePosition;

// Functions
bool init();
void closeAll();


bool init()
{
    // Initialisation flag
    bool success = true;

    // Initialise SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not be initialised! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow( "The World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                // Initialise Renderer Colour
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                // Initialise PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialise! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                // Initialise TTF loading
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialise! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}


void closeAll()
{
    // Free Loaded Images
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;
    
    // Destroy Window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


int main( int argc, char* args[] )
{
    // Start up SDL and create window
    if( !init() ){
        printf( "Failed to initialise!\n" );
    }
    else
    {
        // Main loop flag
        bool quit = false;

        // Frame counter
        TW_FPSTimer fpsTimer;
        TW_FPSTimer_Init( &fpsTimer );
        
        int countedFrames = 0;
        char fpsText[50];

        // Event handler
        SDL_Event e;

        // Time
        TW_Timer mainTimer;
        TW_Timer_Init( &mainTimer, false );
        char timeText[50] = "Time since reset: 0ms";
        
        // Background
        struct LTexture gBackground;
        LTexture_LoadImage( &gBackground, gRenderer, "src/images/backgrounds/day.png" );

        // Text
        // gFontTitle = TTF_OpenFont( "src/assets/fonts/dejavu/DejaVuSerif.ttf", 28 );
        // if( gFontTitle == NULL )
        // {
        //     printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        //     quit = true;
        // }
        // SDL_Color textTitleColour = { 0, 0, 0 };
        // struct LTexture gTitleText;
        // if( !( LTexture_LoadText( &gTitleText, gRenderer, "New game!", gFontTitle, textTitleColour ) ) )
        // {
        //     printf( "Failed to render texture!\n" );
        //     quit = true;
        // }
        SDL_Color textNormalColour = { 0, 0, 0 };
        // Title
        struct TW_Text gTitle;
        TW_Text_FastInit( &gTitle, "My games title :D" );
        TW_Text_SetFont( &gTitle, gTitle.fontName, 28 );
        TW_Text_Render_Texture( &gTitle, gRenderer );
        // printf( "what is my font? %s\n", gTitle.fontName );
        // TW_Text_Init( &gTitle, "My new game! YAY!!", "../src/assets/fonts/dejavu/DejaVuSerif.ttf", 16, textNormalColour );

        // This is now repeatable code and should probably be packaged away in its own special little class - to do
        gFontNormal = TTF_OpenFont( "src/assets/fonts/dejavu/DejaVuSerif.ttf", 16 );
        if( gFontNormal == NULL )
        {
            printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
            quit = true;
        }
        
        struct LTexture gMouseText;
        if( !( LTexture_LoadText( &gMouseText, gRenderer, "Mouse Position: X=0, Y=0", gFontNormal, textNormalColour ) ) )
        {
            printf( "Failed to render texture!\n" );
            quit = true;
        }
        
        // struct LTexture gTimeText;
        // if( !( LTexture_LoadText( &gTimeText, gRenderer, "Time since reset: 0ms", gFontNormal, textNormalColour ) ) )
        // {
        //     printf( "Failed to render texture!\n" );
        //     quit = true;
        // }
        TW_Text gTimeText;
        TW_Text_FastInit( &gTimeText, timeText );
        TW_Text_Render_Texture( &gTimeText, gRenderer );

        struct LTexture gFPSText;
        if( !( LTexture_LoadText( &gFPSText, gRenderer, "FPS: 0", gFontNormal, textNormalColour ) ) )
        {
            printf( "Failed to render texture!\n" );
            quit = true;
        }

        // Mouse
        MousePosition mousePosition = { 0, 0 };
        char mousePositionText[50];

        // Sprite
        const int WALKING_ANIMATION_FRAMES = 4;
        const int SPRITE_HEIGHT = 32;
        const int SPRITE_WIDTH = 32;
        SDL_Rect gSprite[ WALKING_ANIMATION_FRAMES ];
        // Controls
        int frame = 0;
        SDL_RendererFlip flipType = SDL_FLIP_NONE;
        double degrees = 0;
        double angle_increment = 30;

        struct LTexture gSpriteSheet;
        if( !( LTexture_LoadImage( &gSpriteSheet, gRenderer, "src/images/sprites/player.png" ) ) )
        {
            printf( "Failed to load walking animation texture.\n" );
        }
        else
        {
            // Set sprite animation frames
            // An assumption is being made that the frames go from left to right only.
            for( int f = 0; f < WALKING_ANIMATION_FRAMES; f++ )
            {
                gSprite[ f ].x = f * SPRITE_WIDTH;
                gSprite[ f ].y = 0;
                gSprite[ f ].w = SPRITE_WIDTH;
                gSprite[ f ].h = SPRITE_HEIGHT;
            }
        }

        while( !quit )
        {
            while( SDL_PollEvent( &e ) != 0 )
            {
                // Window Event
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                // Keyboard Event
                else if( e.type == SDL_KEYDOWN )
                {
                    switch( e.key.keysym.sym )
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    
                    // No flip
                    case SDLK_s:
                        flipType = SDL_FLIP_NONE;
                        break;

                    // Flip horizontally
                    case SDLK_a:
                        flipType = SDL_FLIP_HORIZONTAL;
                        break;
                    
                    // Flip vertically
                    case SDLK_w:
                        flipType = SDL_FLIP_VERTICAL;
                        break;

                    // Rotate clockwise
                    case SDLK_RIGHT:
                        degrees += angle_increment;
                        if( degrees >= 360 )
                        {
                            degrees -= 360;
                        }
                        break;
                    
                    // Rotate anti-clockwise
                    case SDLK_LEFT:
                        degrees -= angle_increment;
                        if( degrees < 0 )
                        {
                            degrees += 360;
                        }
                        break;
                    
                    // Reset angle
                    case SDLK_DOWN:
                        degrees = 0;
                        break;
                    
                    // Reset clock
                    case SDLK_RETURN:
                    TW_Timer_Reset( &mainTimer );
                    break;

                    // Pause/resume clock
                    case SDLK_SPACE:
                    if( mainTimer.paused )
                    {
                        TW_Timer_Resume( &mainTimer );
                    }
                    else
                    {
                        TW_Timer_Pause( &mainTimer );
                    }
                    break;

                    default:
                        break;
                    }
                }

                // Mouse Event
                else if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                {
                    SDL_GetMouseState( &mousePosition.x, &mousePosition.y );
                    
                    snprintf(mousePositionText, 50, "Mouse Position: X=%d, Y=%d", mousePosition.x, mousePosition.y);

                    if( e.type == SDL_MOUSEBUTTONDOWN )
                    {
                        strcat(mousePositionText, " - KEYDOWN");
                    }

                    if( !( LTexture_LoadText( &gMouseText, gRenderer, mousePositionText, gFontNormal, textNormalColour ) ) )
                    {
                        printf( "Failed to render texture!\n" );
                        quit = true;
                    }
                }
            }

            // Update time
            snprintf( timeText, 50, "Time since reset: %dms", TW_Timer_GetTime( &mainTimer ) );
            TW_Text_Render_Texture( &gTimeText, gRenderer );

            // Update FPS
            snprintf(fpsText, 50, "FPS: %.2f", TW_FPSTimer_GetFPS( &fpsTimer ) );
            if( !( LTexture_LoadText( &gFPSText, gRenderer, fpsText, gFontNormal, textNormalColour ) ) )
            {
                printf( "Failed to render texture!\n" );
                quit = true;
            }

            // Update the surface
            SDL_RenderClear( gRenderer );
            
            // Render background
            LTexture_Render( &gBackground, gRenderer, 0, 0, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render title text
            LTexture_Render( &gTitle.renderedText.mTexture, gRenderer, ( SCREEN_WIDTH - gTitle.renderedText.mWidth ) / 2, 10, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render mouse text
            LTexture_Render( &gMouseText, gRenderer, ((SCREEN_WIDTH - gMouseText.mWidth) / 2), 50, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render time text
            LTexture_Render( &gTimeText.renderedText.mTexture, gRenderer, ((SCREEN_WIDTH - gTimeText.renderedText.mWidth) / 2), 75, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render FPS text
            LTexture_Render( &gFPSText, gRenderer, ((SCREEN_WIDTH - gFPSText.mWidth) / 2), 100, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render sprite
            SDL_Rect* gSpriteFrame = &gSprite[ frame ];
            LTexture_Render( &gSpriteSheet, gRenderer, 235, 235, gSpriteFrame, degrees, NULL, flipType );
            frame = ( frame + 1 ) % WALKING_ANIMATION_FRAMES;

            // Update screen
            SDL_RenderPresent( gRenderer );

            // Update frames counter
            TW_FPSTimer_Update( &fpsTimer );

            // Cap framerate at 60fps
            int frameTicks = TW_FPSTimer_GetFPS( &fpsTimer );

            if( frameTicks < SCREEN_TICKS_PER_FRAME )
            {
                SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
            }
        }

        // LTexture_Free( &gText );
        TW_Timer_Free( &fpsTimer );
        TW_Timer_Free( &mainTimer );
        LTexture_Free( &gSpriteSheet );
        LTexture_Free( &gBackground );
    }

    // Free resources and close SDL
    closeAll();

    return 0;
}
