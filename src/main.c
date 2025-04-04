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
    // This is no longer done... should probably be.
    // SDL_DestroyTexture( gTexture );
    // gTexture = NULL;
    
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

        // Mouse
        MousePosition mousePosition = { 0, 0 };
        char mousePositionText[50] = "Mouse Position: X=0, Y=0";

        // Frame counter
        TW_FPSTimer fpsTimer;
        TW_FPSTimer_Init( &fpsTimer );
        int countedFrames = 0;
        char fpsText[50] = "FPS: 0.00";

        // Event handler
        SDL_Event e;

        // Time
        TW_Timer mainTimer;
        TW_Timer_Init( &mainTimer, false );
        char timeText[50] = "Time since reset: 0ms";
        
        // Background
        TW_Texture gBackground;
        TW_Texture_LoadImage( &gBackground, gRenderer, "src/images/backgrounds/day.png" );

        // Text
        SDL_Color textNormalColour = { 0, 0, 0 };

        // Title
        struct TW_Text gTitle;
        TW_Text_FastInit( &gTitle, "My games title :D" );
        TW_Text_SetFont( &gTitle, gTitle.fontName, 28 );
        if ( ! TW_Text_Render_Texture( &gTitle, gRenderer ) )
        {
            printf( "ERROR: Failed to render texture - Title\n" );
            quit = true;
        }
        
        // Mouse Position
        TW_Text gMouseText;
        TW_Text_FastInit( &gMouseText, mousePositionText );
        if( ! TW_Text_Render_Texture( &gMouseText, gRenderer ) )
        {
            printf( "ERROR: Failed to render texture - Mouse Text\n" );
            quit = true;
        }
        
        // Time
        TW_Text gTimeText;
        TW_Text_FastInit( &gTimeText, timeText );
        if( ! TW_Text_Render_Texture( &gTimeText, gRenderer ) )
        {
            printf( "ERROR: Failed to render texture - Time Text\n" );
            quit = true;
        }

        // FPS
        TW_Text gFPSText;
        TW_Text_FastInit( &gFPSText, fpsText );
        if( ! TW_Text_Render_Texture( &gFPSText, gRenderer ) )
        {
            printf( "ERROR: Failed to render texture - FPS Text\n" );
            quit = true;
        }

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

        TW_Texture gSpriteSheet;
        if( !( TW_Texture_LoadImage( &gSpriteSheet, gRenderer, "src/images/sprites/player.png" ) ) )
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

                    if( ! TW_Text_Render_Texture( &gMouseText, gRenderer ) )
                    {
                        printf( "ERROR: Failed to render texture - Mouse Text\n" );
                        quit = true;
                    }
                }
            }

            // Update time
            snprintf( timeText, 50, "Time since reset: %dms", TW_Timer_GetTime( &mainTimer ) );
            if( ! TW_Text_Render_Texture( &gTimeText, gRenderer ) )
            {
                printf( "ERROR: Failed to render texture - Time Text\n" );
                quit = true;
            }

            // Update FPS
            snprintf(fpsText, 50, "FPS: %.2f", TW_FPSTimer_GetFPS( &fpsTimer ) );
            if( ! TW_Text_Render_Texture( &gFPSText, gRenderer ) )
            {
                printf( "ERROR: Failed to render texture - FPS Text\n" );
                quit = true;
            }

            // Update the surface
            SDL_RenderClear( gRenderer );
            
            // Render background
            TW_Texture_Render( &gBackground, gRenderer, 0, 0, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render title text
            TW_Texture_Render( &gTitle.renderedText.texture, gRenderer, ( SCREEN_WIDTH - gTitle.renderedText.width ) / 2, 10, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render mouse text
            TW_Texture_Render( &gMouseText.renderedText.texture, gRenderer, ((SCREEN_WIDTH - gMouseText.renderedText.width) / 2), 50, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render time text
            TW_Texture_Render( &gTimeText.renderedText.texture, gRenderer, ((SCREEN_WIDTH - gTimeText.renderedText.width) / 2), 75, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render FPS text
            TW_Texture_Render( &gFPSText.renderedText.texture, gRenderer, ((SCREEN_WIDTH - gFPSText.renderedText.width) / 2), 100, NULL, 0.0, NULL, SDL_FLIP_NONE );

            // Render sprite
            SDL_Rect* gSpriteFrame = &gSprite[ frame ];
            TW_Texture_Render( &gSpriteSheet, gRenderer, 235, 235, gSpriteFrame, degrees, NULL, flipType );
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


        // Free resources
        TW_Timer_Free( &fpsTimer );
        TW_Timer_Free( &mainTimer );
        TW_Texture_Free( &gTitle );
        TW_Texture_Free( &gMouseText );
        TW_Texture_Free( &gTimeText );
        TW_Texture_Free( &gFPSText );
        TW_Texture_Free( &gSpriteSheet );
        TW_Texture_Free( &gBackground );
    }

    // Free resources and close SDL
    closeAll();

    return 0;
}
