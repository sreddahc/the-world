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

// --- DEVELOPER ZONE !! DANGER !! COMMENTS MAY NOT EXIST ---

// Renders all entities in a scene - Developers note: This should probably be broken up...
void TW_Scene_Render( TW_Scene* self )
{
    for( int index = 0; index < self->size; index++ ){
        // For each Component in an Entity
        TW_Entity_Render( self->entities[ index ] );
    }
}