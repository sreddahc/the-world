#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "renderer/renderer.h"
#include "renderer/text.h"
#include "renderer/animation.h"
#include "engine/timer.h"
#include "ecs/scene.h"
#include "engine/maths.h"
#include "engine/gametimer.h"

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
                TW_GameTimer_Create();
                TW_GameTimer_SetFrameLimit( SCREEN_FPS );
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

        // Event handler
        SDL_Event e;
        
        // Main scene
        TW_Scene* sceneMain = TW_Scene_Create();

        // Background
        TW_Texture* gBackground = TW_Texture_CreateTexture();
        TW_Texture_LoadImage( gBackground, "src/images/backgrounds/day.png" );
        TW_Entity* entityBackground = TW_Entity_Create();
        TW_Entity_AddComponent( entityBackground, TW_Component_Create( TW_COMPONENT_TEXTURE, gBackground ) );
        TW_Scene_AddEntity( sceneMain, entityBackground );

        // Title Entity
        TW_Text* gTitle = TW_Text_Create( "PROBS A COOL GAME", NULL, 32, TW_Colour_Create( 0x80, 0x00, 0x80, 0xff ) );
        TW_Entity* entityTitle = TW_Entity_Create();
        TW_Entity_AddComponent( entityTitle, TW_Component_Create( TW_COMPONENT_TEXT, gTitle ) );
        TW_Entity_AddComponent( entityTitle, TW_Component_Create( TW_COMPONENT_TRANSFORM, TW_Transform_Create( SCREEN_WIDTH / 2, 30, 0.0, 1.0 ) ) );
        TW_Vector2_Set(TW_Entity_GetComponent( entityTitle, TW_COMPONENT_TRANSFORM )->transform->centre, gTitle->texture->width / 2, gTitle->texture->height / 2 );
        TW_Scene_AddEntity( sceneMain, entityTitle );

        // Mouse Position Entity
        TW_Vector2* mousePosition = TW_Vector2_Create( 0, 0 );
        char mousePositionText[50] = "Mouse Position: X=0, Y=0";
        TW_Text* gMouseText = TW_Text_Create( mousePositionText, NULL, 0, NULL );
        TW_Entity* entityMouseText = TW_Entity_Create();
        TW_Entity_AddComponent( entityMouseText, TW_Component_Create( TW_COMPONENT_TEXT, gMouseText ) );
        TW_Entity_AddComponent( entityMouseText, TW_Component_Create( TW_COMPONENT_TRANSFORM, TW_Transform_Create( 5, 5, 0.0, 1.0 ) ) );
        TW_Scene_AddEntity( sceneMain, entityMouseText );

        // Player Entity
        TW_Animation* gPlayer = TW_Animation_Create( TW_Sprite_Create( "src/images/sprites/player.png", 32, 32 ), 4, (int[]){ 0, 1, 2, 3 } );
        TW_Entity* entityPlayer = TW_Entity_Create();
        TW_Entity_AddComponent( entityPlayer, TW_Component_Create( TW_COMPONENT_ANIMATION, gPlayer ) );
        TW_Entity_AddComponent( entityPlayer, TW_Component_Create( TW_COMPONENT_TRANSFORM, TW_Transform_Create( 200, 200, 0.0, 1.0 ) ) );
        TW_Scene_AddEntity( sceneMain, entityPlayer );

        // Time
        TW_Timer mainTimer;
        TW_Timer_Init( &mainTimer, false );
        char timeText[50] = "Time since reset: 0ms";
        TW_Text* gTimeText = TW_Text_Create( timeText, NULL, 0, NULL );
        TW_Entity* entityTimeText = TW_Entity_Create();
        TW_Entity_AddComponent( entityTimeText, TW_Component_Create( TW_COMPONENT_TEXT, gTimeText ) );
        TW_Entity_AddComponent(entityTimeText, TW_Component_Create( TW_COMPONENT_TRANSFORM, TW_Transform_Create( 5, 25, 0.0, 1.0 ) ) );
        TW_Scene_AddEntity( sceneMain, entityTimeText );

        // FPS
        char fpsText[50] = "FPS: 0.00";
        TW_Text* gFPSText = TW_Text_Create( fpsText, NULL, 0, NULL );
        TW_Entity* entityFPSText = TW_Entity_Create();
        TW_Entity_AddComponent( entityFPSText, TW_Component_Create( TW_COMPONENT_TEXT, gFPSText ) );
        TW_Entity_AddComponent(entityFPSText, TW_Component_Create( TW_COMPONENT_TRANSFORM, TW_Transform_Create( 5, 45, 0.0, 1.0 ) ) );
        TW_Scene_AddEntity( sceneMain, entityFPSText );

        // Delta Time
        char deltaTimeText[50] = "Delta Time: 0.00000 ms";
        TW_Text* gDeltaTimeText = TW_Text_Create( deltaTimeText, NULL, 0, NULL );
        TW_Entity* entityDeltaTimeText = TW_Entity_Create();
        TW_Entity_AddComponent( entityDeltaTimeText, TW_Component_Create( TW_COMPONENT_TEXT, gDeltaTimeText ) );
        TW_Entity_AddComponent(entityDeltaTimeText, TW_Component_Create( TW_COMPONENT_TRANSFORM, TW_Transform_Create( 5, 65, 0.0, 1.0 ) ) );
        TW_Scene_AddEntity( sceneMain, entityDeltaTimeText );

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
                    
                    // Reset clock
                    case SDLK_RETURN:
                    TW_Timer_Reset( &mainTimer );
                    break;

                    // Pause/resume clock
                    case SDLK_SPACE:
                    if( mainTimer.paused )
                    {
                        TW_Timer_Resume( &mainTimer );
                        for( int i = 0; i < sceneMain->size; i++ )
                        {
                            TW_Component* tempAnimation = TW_Entity_GetComponent( sceneMain->entities[ i ], TW_COMPONENT_ANIMATION );
                            if( tempAnimation != NULL )
                            {
                                tempAnimation->animation->paused = false;
                            }
                        }
                    }
                    else
                    {
                        TW_Timer_Pause( &mainTimer );
                        for( int i = 0; i < sceneMain->size; i++ )
                        {
                            TW_Component* tempAnimation = TW_Entity_GetComponent( sceneMain->entities[ i ], TW_COMPONENT_ANIMATION );
                            if( tempAnimation != NULL )
                            {
                                tempAnimation->animation->paused = true;
                            }
                        }
                    }
                    break;

                    default:
                        break;
                    }
                }

                // Mouse Event
                else if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                {
                    SDL_GetMouseState( &mousePosition->x, &mousePosition->y );
                    
                    snprintf(mousePositionText, 50, "Mouse Position: X=%d, Y=%d", mousePosition->x, mousePosition->y);

                    if( e.type == SDL_MOUSEBUTTONDOWN )
                    {
                        strcat(mousePositionText, " - KEYDOWN");
                    }

                    TW_Text_Update( gMouseText );

                }
            }

            // Update time
            snprintf( timeText, 50, "Time since reset: %d ms", TW_Timer_GetTime( &mainTimer ) );
            TW_Text_Update( gTimeText );

            // Update FPS
            snprintf( fpsText, 50, "FPS: %.2f ", TW_GameTimer_GetFPS() );
            TW_Text_Update( gFPSText );

            // Update the surface
            SDL_RenderClear( TW_GetRenderer() );
            TW_GameTimer_Update();

            snprintf( deltaTimeText, 50, "Delta Time: %.5f ms", TW_GameTimer_GetTimeDelta() );
            TW_Text_Update( gDeltaTimeText );

            // For each Entity in a Scene
            TW_Scene_Render( sceneMain );

            // // Update screen
            SDL_RenderPresent( TW_GetRenderer() );
            TW_GameTimer_LimitFrameRate();
        }

        // Free resources
        TW_Vector2_Free( mousePosition );
        TW_Timer_Free( &mainTimer );
        TW_Scene_Free( sceneMain );
        TW_GameTimer_Free();
    }

    // Free resources and close SDL
    closeAll();

    return 0;
}
