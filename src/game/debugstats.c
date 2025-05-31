#include "debugstats.h"


// This is a bit ugly... I think but we can clean this later.
static char mouseStatus[50] = "Mouse Position: X=0, Y=0";
static char timerStatus[50] = "Game runtime: 0 ms";
static char fpsStatus[50] = "FPS: 0.00";
static char deltaTimeStatus[50] = "Delta Time: 0.00000 ms";


// The think function for the mouse debug component
void TW_DebugStats_Mouse_Think( TW_Entity* entity )
{
    if( TW_InputHandler_CheckMouseMove() == true || TW_InputHandler_CheckMouseDown( 1 ) || TW_InputHandler_CheckMouseUp( 1 ) )
    {
        int x = 0;
        int y = 0;
        SDL_GetMouseState( &x, &y );
        snprintf( mouseStatus, 50, "Mouse Position: X=%d, Y=%d", x, y );

        if( TW_InputHandler_CheckMouseDown( 1 ) == true )
        {
            strcat(mouseStatus, " - KEYDOWN");
        }

        if( entity != NULL )
        {
            TW_Component* textComponent = TW_Entity_GetComponent( entity, TW_C_TEXT );
            if( textComponent != NULL )
            {
                TW_Text_Update( textComponent->text );
            }
        }
    }
}


// The think function for the time debug component
void TW_DebugStats_Time_Think( TW_Entity* entity )
{
    snprintf( timerStatus, 50, "Game runtime: %d ms", (int)TW_GameState_GetTime() );
    if( entity != NULL )
    {
        TW_Component* textComponent = TW_Entity_GetComponent( entity, TW_C_TEXT );
        if( textComponent != NULL )
        {
            TW_Text_Update( textComponent->text );
        }
    }
}


// The think function for the FPS debug component
void TW_DebugStats_FPS_Think( TW_Entity* entity )
{
    snprintf( fpsStatus, 50, "FPS: %.2f ", TW_GameState_GetFPS() );
    if( entity != NULL)
    {
        TW_Component* textComponent = TW_Entity_GetComponent( entity, TW_C_TEXT );
        if( textComponent != NULL )
        {
            TW_Text_Update( textComponent->text );
        }
    }
}


// The think function for the delta time debug component
void TW_DebugStats_DeltaTime_Think( TW_Entity* entity )
{
    snprintf( deltaTimeStatus, 50, "Delta Time: %.5f ms", TW_GameState_GetDeltaTime() );
    if( entity != NULL)
    {
        TW_Component* textComponent = TW_Entity_GetComponent( entity, TW_C_TEXT );
        if( textComponent != NULL )
        {
            TW_Text_Update( textComponent->text );
        }
    }
}


// Generates a number of entities and adds them to a target scene for the purposes of debugging
void TW_DebugStats_Create( TW_Scene* self )
{
    // Mouse
    TW_Entity* entityMouse = TW_Entity_Create();
    TW_Scene_AddEntity( self, entityMouse );
    TW_Text* textMouse = TW_Text_Create( mouseStatus, NULL, 0, NULL );
    textMouse->texture->overlay = true;
    TW_Component* cTextMouse = TW_Component_Create( TW_C_TEXT, textMouse );
    TW_Entity_AddComponent( entityMouse, cTextMouse );
    TW_Transform* transformMouse = TW_Transform_Create( 5, 5, 0.0, 1.0 );
    TW_Component* cTransformMouse = TW_Component_Create( TW_C_TRANSFORM, transformMouse );
    TW_Entity_AddComponent( entityMouse, cTransformMouse );
    TW_Think* thinkMouse = TW_Think_Create( TW_DebugStats_Mouse_Think );
    TW_Component* cThinkMouse = TW_Component_Create( TW_C_THINK, thinkMouse );
    TW_Entity_AddComponent( entityMouse, cThinkMouse );

    // Timer
    TW_Entity* entityTime = TW_Entity_Create();
    TW_Scene_AddEntity( self, entityTime );
    TW_Text* textTime = TW_Text_Create( timerStatus, NULL, 0, NULL );
    textTime->texture->overlay = true;
    TW_Component* cTextTime = TW_Component_Create( TW_C_TEXT, textTime );
    TW_Entity_AddComponent( entityTime, cTextTime );
    TW_Transform* transformTime = TW_Transform_Create( 5, 25, 0.0, 1.0 );
    TW_Component* cTransformTime = TW_Component_Create( TW_C_TRANSFORM, transformTime );
    TW_Entity_AddComponent( entityTime, cTransformTime );
    TW_Think* thinkTime = TW_Think_Create( TW_DebugStats_Time_Think );
    TW_Component* cThinkTime = TW_Component_Create( TW_C_THINK, thinkTime );
    TW_Entity_AddComponent( entityTime, cThinkTime );

    // FPS
    TW_Entity* entityFPS = TW_Entity_Create();
    TW_Scene_AddEntity( self, entityFPS );
    TW_Text* textFPS = TW_Text_Create( fpsStatus, NULL, 0, NULL );
    textFPS->texture->overlay = true;
    TW_Component* cTextFPS = TW_Component_Create( TW_C_TEXT, textFPS );
    TW_Entity_AddComponent( entityFPS, cTextFPS );
    TW_Transform* transformFPS = TW_Transform_Create( 5, 45, 0.0, 1.0 );
    TW_Component* cTransformFPS = TW_Component_Create( TW_C_TRANSFORM, transformFPS );
    TW_Entity_AddComponent( entityFPS, cTransformFPS );
    TW_Think* thinkFPS = TW_Think_Create( TW_DebugStats_FPS_Think );
    TW_Component* cThinkFPS = TW_Component_Create( TW_C_THINK, thinkFPS );
    TW_Entity_AddComponent( entityFPS, cThinkFPS );

    // Delta Time
    TW_Entity* entityDeltaTime = TW_Entity_Create();
    TW_Scene_AddEntity( self, entityDeltaTime );
    TW_Text* textDeltaTime = TW_Text_Create( deltaTimeStatus, NULL, 0, NULL );
    textDeltaTime->texture->overlay = true;
    TW_Component* cTextDeltaTime = TW_Component_Create( TW_C_TEXT, textDeltaTime );
    TW_Entity_AddComponent( entityDeltaTime, cTextDeltaTime );
    TW_Transform* transformDeltaTime = TW_Transform_Create( 5, 65, 0.0, 1.0 );
    TW_Component* cTransformDeltaTime = TW_Component_Create( TW_C_TRANSFORM, transformDeltaTime );
    TW_Entity_AddComponent( entityDeltaTime, cTransformDeltaTime );
    TW_Think* thinkDeltaTime = TW_Think_Create( TW_DebugStats_DeltaTime_Think );
    TW_Component* cThinkDeltaTime = TW_Component_Create( TW_C_THINK, thinkDeltaTime );
    TW_Entity_AddComponent( entityDeltaTime, cThinkDeltaTime );
}

// Free the resources used by a debug status object
void TW_DebugStats_Free()
{
    
}