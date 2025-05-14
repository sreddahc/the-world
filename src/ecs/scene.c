#include "scene.h"


// Creates a scene to store entities in.
TW_Scene* TW_Scene_Create()
{
    TW_Scene* scene = malloc( sizeof( TW_Scene ) );
    scene->size = 0;
    scene->entities = NULL;
    return scene;
}


// Free the resources used by a scene.
void TW_Scene_Free( TW_Scene* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        TW_Entity_Free( self->entities[ index ] );
    }
    self->size = 0;
    free( self );
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
            self->entities = malloc( self->size * sizeof( TW_Entity* ) );
        }
        else
        {
            TW_Entity** oldEntities = self->entities;
            self->entities = malloc( self->size * sizeof( TW_Entity* ) );
            memcpy( self->entities, oldEntities, ( self->size - 1 ) * sizeof( TW_Entity* ) );
            free( oldEntities );
        }
        self->entities[ self->size - 1 ] = entity;
        entity->parent = self;
    }
}


// Run logic components in a scene.
void TW_Scene_RunLogic( TW_Scene* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        TW_Entity_RunLogic( self->entities[ index ] );
    }
}


// Run physics engine on a scene.
void TW_Scene_RunPhysics( TW_Scene* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        TW_Entity_RunPhysics( self->entities[ index ] );
    }
}


// Render all entities in a scene.
void TW_Scene_Render( TW_Scene* self )
{
    for( int index = 0; index < self->size; index++ ){
        // For each Component in an Entity
        TW_Entity_Render( self->entities[ index ] );
    }
}


// Clear the state of all entities in a scene. Run at the end of every game loop.
void TW_Scene_Clear( TW_Scene* self )
{
    for( int index = 0; index < self->size; index++ )
    {
        TW_Entity_Clear( self->entities[ index ] );
    }
}
