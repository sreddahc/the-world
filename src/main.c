#include "renderer/renderer.h"
#include "engine/timer.h"
#include "game/player.h"
#include "game/platform.h"
#include "game/debugstats.h"

// Global variables
// Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;
const int SCREEN_FPS = 60;

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
            TW_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( TW_GetRenderer() == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                // Initialise Renderer Colour
                SDL_SetRenderDrawColor( TW_GetRenderer(), 0x00, 0x00, 0x00, 0xff );

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

                // Initialise the game timer
                TW_GameState_Create();
                TW_GameState_SetFrameLimit( SCREEN_FPS );

                // Initialse input handler
                TW_InputHandler_Create();
            }
        }
    }

    return success;
}


void closeAll()
{
    // Destroy Window
    TW_DestroyRenderer();
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

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

        // Main scene
        TW_Scene* sceneMain = TW_Scene_Create();

        // Background
        TW_Texture* gBackground = TW_Texture_CreateTexture();
        TW_Texture_LoadImage( gBackground, "src/assets/images/backgrounds/day.png" );
        TW_Entity* entityBackground = TW_Entity_Create();
        TW_Entity_AddComponent( entityBackground, TW_Component_Create( TW_C_TEXTURE, gBackground ) );
        TW_Scene_AddEntity( sceneMain, entityBackground );

        // Title Entity
        TW_Text* gTitle = TW_Text_Create( "PROBS A COOL GAME", NULL, 32, TW_Colour_Create( 0x80, 0x00, 0x80, 0xff ) );
        TW_Entity* entityTitle = TW_Entity_Create();
        TW_Entity_AddComponent( entityTitle, TW_Component_Create( TW_C_TEXT, gTitle ) );
        TW_Entity_AddComponent( entityTitle, TW_Component_Create( TW_C_TRANSFORM, TW_Transform_Create( SCREEN_WIDTH / 2, 30, 0.0, 1.0 ) ) );
        TW_Vector2_Set(TW_Entity_GetComponent( entityTitle, TW_C_TRANSFORM )->transform->centre, gTitle->texture->width / 2, gTitle->texture->height / 2 );
        TW_Scene_AddEntity( sceneMain, entityTitle );

        // Platform Entities
        for( int index = 0; index < 5; index ++ )
        {
            int xPosition = 200;
            switch ( index )
            {
                case 0:
                    TW_Platform_Create( sceneMain, TW_PLATFORM_LEFT, xPosition, 250 );
                    break;

                case 4:
                    TW_Platform_Create( sceneMain, TW_PLATFORM_RIGHT, xPosition + ( index * 35 ), 250 );
                    break;

                default:
                    TW_Platform_Create( sceneMain, TW_PLATFORM_MIDDLE, xPosition + ( index * 35 ), 250 );
                    break;
            }
        }

        // Player Entity
        TW_Player_Create( sceneMain, 200, 200 );

        // Time
        // TW_Timer* mainTimer = TW_Timer_Create( false );
        // char timeText[50] = "Time since reset: 0ms";
        // TW_Text* gTimeText = TW_Text_Create( timeText, NULL, 0, NULL );
        // TW_Entity* entityTimeText = TW_Entity_Create();
        // TW_Entity_AddComponent( entityTimeText, TW_Component_Create( TW_C_TEXT, gTimeText ) );
        // TW_Entity_AddComponent(entityTimeText, TW_Component_Create( TW_C_TRANSFORM, TW_Transform_Create( 500, 125, 0.0, 1.0 ) ) );
        // TW_Scene_AddEntity( sceneMain, entityTimeText );

        // Debug Status
        TW_DebugStats_Create( sceneMain );

        while( !quit )
        {
            while( TW_InputHandler_Poll() == true )
            {
                quit = TW_InputHandler_CheckQuit();

                if( TW_InputHandler_CheckKeyPressed( SDLK_ESCAPE ) == true )
                {
                    quit = true;
                }
                
                TW_Scene_Run( sceneMain );
            }

            // snprintf( timeText, 50, "Time since reset: %ld ms", TW_Timer_GetTime( mainTimer ) );
            // TW_Text_Update( gTimeText );

            // Update the surface
            SDL_RenderClear( TW_GetRenderer() );
            TW_GameState_Update();

            TW_Scene_Run( sceneMain );

            // For each Entity in a Scene
            TW_Scene_Render( sceneMain );

            // // Update screen
            SDL_RenderPresent( TW_GetRenderer() );
            TW_GameState_LimitFrameRate();
        }

        // Free resources
        TW_DebugStats_Free();
        TW_Scene_Free( sceneMain );
        TW_GameState_Free();
    }

    // Free resources and close SDL
    closeAll();

    return 0;
}
