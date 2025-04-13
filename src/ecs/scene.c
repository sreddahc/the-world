#include "scene.h"


// Creates a scene to store entities in.
TW_Scene* TW_Scene_Create()
{
    TW_Scene* scene = malloc( sizeof( TW_Scene ) );
    scene->size = 0;
    scene->entities = NULL;
    return scene;
}


// TW_Scene_AddEntity - Creates a scene to store entities in.
void TW_Scene_AddEntity( TW_Scene* self, TW_Entity* entity )
{
    self->size += 1;
    if( self->size > 0 )
    {
        // Create space and add entities. Memory handling for exisiting entities.
        if( self->entities == NULL )
        {
            self->entities = malloc( self->size * sizeof( TW_Entity ) );
            self->entities[ self->size - 1 ] = entity;
        }
        else
        {
            TW_Entity* oldEntities = self->entities;
            self->entities = malloc( self->size * sizeof( TW_Entity ) );
            memcpy( self->entities, oldEntities, ( self->size - 1 ) * sizeof( TW_Entity ) );
            self->entities[ self->size - 1 ] = entity;
        }
    }
}


// TW_Scene_Free - Free the resources used by a scene.
void TW_Scene_Free( TW_Scene* self )
{}

// Renders all entities in a scene - Developers note: This should probably be broken up...
void TW_Scene_Render( TW_Scene* self )
{
    for( int i = 0; i < self->size; i++ ){
        // For each Component in an Entity
        for( int j = 0; j < self->entities[ i ]->size; j++ )
        {
            // Render visual components
            switch ( self->entities[ i ]->components[ j ]->type )
            {
            case TW_COMPONENT_TEXTURE:
                TW_Texture_Render( self->entities[ i ]->components[ j ]->value );
                break;

            case TW_COMPONENT_TEXT:
                TW_Text_Render( self->entities[ i ]->components[ j ]->value );
                break;
            
                case TW_COMPONENT_SPRITE:
                TW_Sprite_Render( self->entities[ i ]->components[ j ]->value );
                break;
            
            case TW_COMPONENT_ANIMATION:
                TW_Animation_Render( self->entities[ i ]->components[ j ]->value );
                break;
            
            default:
                break;
            }
        }
    }
}