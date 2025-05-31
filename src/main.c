#include "renderer/renderer.h"
#include "engine/timer.h"
#include "engine/camera.h"
#include "engine/level.h"
#include "game/components/player.h"
#include "game/components/platform.h"
#include "game/debugstats.h"

// Global variables
// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int LEVEL_WIDTH = 36 * 35;    // NEEDS TO BE UPDATED
const int LEVEL_HEIGHT = 22 * 35;   // NEEDS TO BE UPDATED
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
                TW_Camera_Create( NULL, SCREEN_WIDTH, SCREEN_HEIGHT );

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

        // Input
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYDOWN, TW_L_KeyDown_Create( SDLK_ESCAPE ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYDOWN, TW_L_KeyDown_Create( SDLK_a ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYDOWN, TW_L_KeyDown_Create( SDLK_d ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYDOWN, TW_L_KeyDown_Create( SDLK_SPACE ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYDOWN, TW_L_KeyDown_Create( SDLK_LSHIFT ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYUP, TW_L_KeyUp_Create( SDLK_a ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYUP, TW_L_KeyUp_Create( SDLK_d ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYUP, TW_L_KeyUp_Create( SDLK_SPACE ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_KEYUP, TW_L_KeyUp_Create( SDLK_LSHIFT ) ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_MOUSEDOWN, TW_L_MouseDown_Create( 1 ) ) ); // Primary button
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_MOUSEMOVE, TW_L_MouseMove_Create() ) );
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_MOUSEUP, TW_L_MouseUp_Create( 1 ) ) ); // Primary button
        TW_InputHandler_AddListener( TW_Listener_Add( TW_L_QUIT, TW_L_Quit_Create() ) );

        // Main scene
        TW_Scene* sceneMain = TW_Scene_Create();

        // Background
        TW_Texture* gBackground = TW_Texture_CreateTexture();
        TW_Texture_LoadImage( gBackground, "src/assets/images/backgrounds/night.png" );
        TW_Entity* entityBackground = TW_Entity_Create();
        TW_Entity_AddComponent( entityBackground, TW_Component_Create( TW_C_TEXTURE, gBackground ) );
        TW_Scene_AddEntity( sceneMain, entityBackground );

        // Title Entity
        TW_Text* gTitle = TW_Text_Create( "PROBS A JANK GAME", NULL, 32, TW_Colour_Create( 0x80, 0x00, 0x80, 0xff ) );
        gTitle->texture->overlay = true;
        TW_Entity* entityTitle = TW_Entity_Create();
        TW_Entity_AddComponent( entityTitle, TW_Component_Create( TW_C_TEXT, gTitle ) );
        TW_Entity_AddComponent( entityTitle, TW_Component_Create( TW_C_TRANSFORM, TW_Transform_Create( SCREEN_WIDTH / 2, 30, 0.0, 1.0 ) ) );
        TW_Vector2_Set(TW_Entity_GetComponent( entityTitle, TW_C_TRANSFORM )->transform->centre, gTitle->texture->width / 2, gTitle->texture->height / 2 );
        TW_Scene_AddEntity( sceneMain, entityTitle );

        TW_Level* currentLevel = TW_Level_Create( sceneMain, LEVEL_WIDTH, LEVEL_HEIGHT );
        TW_GameState_SetLevel( currentLevel );

        int tempLevel[22][36] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 3, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 2, 3, 3, 4, 0, 2, 4, 0, 1, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        // First add platforms
        for( int j = 0; j < 22; j++ )
        {
            for( int i = 0; i < 36; i++ )
            {
                if( tempLevel[ j ][ i ] >= 1 && tempLevel[ j ][ i ] <= 4 )
                {
                    
                    TW_Scene_GeneratePlatform( sceneMain, tempLevel[ j ][ i ] - 1, i * 35, j * 35 );
                }
            }
        }

        // Then add interactable items
        for( int j = 0; j < 22; j++ )
        {
            for( int i = 0; i < 36; i++ )
            {
                if( tempLevel[ j ][ i ] == 5 )
                {
                    TW_Fountain_Generate( sceneMain, TW_PWR_MOON, i * 35, j * 35 );
                }
            }
        }

        // Finally add the player
        for( int j = 0; j < 22; j++ )
        {
            for( int i = 0; i < 36; i++ )
            {
                if( tempLevel[ j ][ i ] == -1 )
                {
                    TW_Scene_GeneratePlayer( sceneMain, i * 35, j * 35 );
                }
            }
        }
        // Set target of camera to player
        for( int index = 0; index < sceneMain->size; index++ )
        {
            TW_Component* pPlayer = TW_Entity_GetComponent( sceneMain->entities[ index ], TW_C_PLAYER );
            if( pPlayer != NULL )
            {
                TW_Camera_SetTarget( sceneMain->entities[ index ] );
                break;
            }
        }

        // Debug Status
        TW_DebugStats_Create( sceneMain );

        while( !quit )
        {
            // Update the surface, reset game state and update listeners with latest events.
            SDL_RenderClear( TW_GetRenderer() );
            TW_GameState_Update();
            TW_InputHandler_UpdateListeners();

            // Check if application should quit:
            if( TW_InputHandler_CheckQuit() || TW_InputHandler_CheckKeyDown( SDLK_ESCAPE ) )
            {
                quit = true;
            }

            TW_Scene* currentScene = TW_Level_GetScene( TW_GameState_GetLevel() );
            if( currentScene != NULL )
            {
                // Run physics engine
                TW_Scene_RunPhysics( currentScene );

                // Run logic engine
                TW_Scene_RunLogic( currentScene );

                // Draw the scene
                TW_Scene_Render( currentScene );

                // Update screen, clear listeners and limit frame rate (if required).
                TW_Scene_Clear( currentScene );
            }

            SDL_RenderPresent( TW_GetRenderer() );
            TW_InputHandler_ClearListeners();
            TW_GameState_LimitFrameRate();
        }

        // Free resources
        TW_DebugStats_Free();
        TW_Scene_Free( sceneMain );
        TW_InputHandler_Free();
        TW_GameState_Free();
    }

    // Free resources and close SDL
    closeAll();

    return 0;
}
