#include "debugstats.h"


static char fpsStatus[50] = "FPS: 0.00";


void TW_DebugStats_FPS_Think( TW_Component* component )
{
    snprintf( fpsStatus, 50, "FPS: %.2f ", TW_GameState_GetFPS() );
    if( component->parent != NULL)
    {
        TW_Component* textComponent = TW_Entity_GetComponent( component->parent, TW_C_TEXT );
        if( textComponent != NULL )
        {
            TW_Text_Update( textComponent->text );
        }
    }
}


void TW_DebugStats_Create( TW_Scene* self )
{
    // Mouse
    TW_Entity* entityMouse = TW_Entity_Create();
    TW_Scene_AddEntity( self, entityMouse );
    TW_Text* textMouse = TW_Text_Create( "Mouse position: x=0, y=0", NULL, 0, NULL );
    TW_Component* cTextMouse = TW_Component_Create( TW_C_TEXT, textMouse );
    TW_Entity_AddComponent( entityMouse, cTextMouse );
    TW_Transform* transformMouse = TW_Transform_Create( 5, 5, 0.0, 1.0 );
    TW_Component* cTransformMouse = TW_Component_Create( TW_C_TRANSFORM, transformMouse );
    TW_Entity_AddComponent( entityMouse, cTransformMouse );

    // Timer
    TW_Entity* entityTime = TW_Entity_Create();
    TW_Scene_AddEntity( self, entityTime );
    TW_Text* textTime = TW_Text_Create( "Time since reset: 0 ms", NULL, 0, NULL );
    TW_Component* cTextTime = TW_Component_Create( TW_C_TEXT, textTime );
    TW_Entity_AddComponent( entityTime, cTextTime );
    TW_Transform* transformTime = TW_Transform_Create( 5, 25, 0.0, 1.0 );
    TW_Component* cTransformTime = TW_Component_Create( TW_C_TRANSFORM, transformTime );
    TW_Entity_AddComponent( entityTime, cTransformTime );
    
    // FPS
    TW_Entity* entityFPS = TW_Entity_Create();
    TW_Scene_AddEntity( self, entityFPS );
    TW_Text* textFPS = TW_Text_Create( fpsStatus, NULL, 0, NULL );
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
    TW_Text* textDeltaTime = TW_Text_Create( "Delta time: 0.00000 ms", NULL, 0, NULL );
    TW_Component* cTextDeltaTime = TW_Component_Create( TW_C_TEXT, textDeltaTime );
    TW_Entity_AddComponent( entityDeltaTime, cTextDeltaTime );
    TW_Transform* transformDeltaTime = TW_Transform_Create( 5, 65, 0.0, 1.0 );
    TW_Component* cTransformDeltaTime = TW_Component_Create( TW_C_TRANSFORM, transformDeltaTime );
    TW_Entity_AddComponent( entityDeltaTime, cTransformDeltaTime );
}