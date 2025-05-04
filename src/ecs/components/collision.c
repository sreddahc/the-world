#include "../scene.h"


// Create a collision object based on provided parameters.
TW_Collision* TW_Collision_Create( int x, int y, int w, int h )
{
    TW_Collision* collision = malloc( sizeof( TW_Collision ) );

    collision->position = TW_Vector2_Create( x, y );
    collision->centre = TW_Vector2_Create( 0, 0 );
    collision->size = TW_Vector2_Create( w, h );
    collision->oldPosition = TW_Vector2_Create( 0, 0 );
    collision->hasPhysics = false;
    collision->fixed = false;
    collision->parent = NULL;
    collision->collisionCount = 0;
    collision->collisionBufferSize = 0;
    collision->collisions = NULL;

    return collision;
}


// Frees the resources used by a collision object.
void TW_Collision_Free( TW_Collision* self )
{
    for( int index = 0; index < self->collisionBufferSize; index++ )
    {
        self->collisions[ index ] = NULL;
    }
    free( self->collisions );
    self->collisionBufferSize = 0;
    self->collisionCount = 0;
    self->parent = NULL;
    self->fixed = false;
    self->hasPhysics = false;
    TW_Vector2_Free( self->size );
    TW_Vector2_Free( self->centre );
    TW_Vector2_Free( self->position );
    TW_Vector2_Free( self->oldPosition );
    free( self );
}


// Test whether current entity collides with a target entity
bool TW_Collision_Check( TW_Entity* self, TW_Entity* target )
{
    if( self != NULL && target != NULL )
    {
        TW_Component* currentTransform = TW_Entity_GetComponent( self, TW_C_TRANSFORM );
        TW_Component* currentCollision = TW_Entity_GetComponent( self, TW_C_COLLISION );
        TW_Component* targetTransform = TW_Entity_GetComponent( target, TW_C_TRANSFORM );
        TW_Component* targetCollision = TW_Entity_GetComponent( target, TW_C_COLLISION );
        if(
            currentTransform != NULL && currentCollision != NULL &&
            targetTransform != NULL && targetCollision != NULL
        )
        {
            // !! Currently ignoring anything to do with "Centre" !!

            // Current dimensions
            int currentTop = currentTransform->transform->position->y + currentCollision->collision->position->y;
            int currentBot = currentTransform->transform->position->y + currentCollision->collision->position->y + currentCollision->collision->size->y;
            int currentLeft = currentTransform->transform->position->x + currentCollision->collision->position->x;
            int currentRight = currentTransform->transform->position->x + currentCollision->collision->position->x + currentCollision->collision->size->x;
            
            // Target dimensions
            int targetTop = targetTransform->transform->position->y + targetCollision->collision->position->y;
            int targetBot = targetTransform->transform->position->y + targetCollision->collision->position->y + targetCollision->collision->size->y;
            int targetLeft = targetTransform->transform->position->x + targetCollision->collision->position->x;
            int targetRight = targetTransform->transform->position->x + targetCollision->collision->position->x + targetCollision->collision->size->x;

            // Check bounds to see if current object is outside of target object on all sides
            if( currentTop >= targetBot )
            {
                return false;
            }
            
            if( targetTop >= currentBot )
            {
                return false;
            }

            if( currentLeft >= targetRight )
            {
                return false;
            }

            if( targetLeft >= currentRight )
            {
                return false;
            }

            return true;
        }
    }

    return false;
}


// Run the collision object. This should be done every game loop as long as the game is not paused.
void TW_Collision_Run( TW_Collision* self )
{
    TW_Component* collision = self->parent;
    TW_Entity* entity = NULL;
    TW_Scene* scene = NULL;

    if( collision != NULL )
    {
        entity = collision->parent;
    }

    if( entity != NULL )
    {
        scene = entity->parent;
    }

    if( scene != NULL )
    {
        for( int index = 0; index < scene->size; index++ )
        {
            if( entity != scene->entities[ index ] )
            {
                if( TW_Collision_Check( entity, scene->entities[ index ] ) == true )
                {
                    // Record collision in collision object if it has not yet been observed.
                    TW_Component* target = TW_Entity_GetComponent( scene->entities[ index ], TW_C_COLLISION );
                    if( target != NULL )
                    {
                        bool alreadyObserved = false;
                        for( int index = 0; index < target->collision->collisionCount; index++ )
                        {
                            if( target->collision->collisions[ index ] == entity )
                            {
                                alreadyObserved = true;
                            }
                        }
                        // If it has not, add collision reference to both entities.
                        if( alreadyObserved == false )
                        {
                            TW_Collision_AddCollisions( self, scene->entities[ index ] );
                            TW_Collision_AddCollisions( target->collision, entity );
                        }
                    }

                    // If objects have physics... apply physics.
                    TW_Collision_Physics( entity, scene->entities[ index ] );
                }
            }
        }
    }
}


// Attempt to resolve the physics of 2 entities which have physics.
void TW_Collision_Physics( TW_Entity* entity1, TW_Entity* entity2 )
{
    TW_Component* c1 = TW_Entity_GetComponent( entity1, TW_C_COLLISION );
    TW_Component* t1 = TW_Entity_GetComponent( entity1, TW_C_TRANSFORM );
    TW_Component* c2 = TW_Entity_GetComponent( entity2, TW_C_COLLISION );
    TW_Component* t2 = TW_Entity_GetComponent( entity2, TW_C_TRANSFORM );

    // Ensure that all required components exist.
    if ( c1 != NULL && t1 != NULL && c2 != NULL && t2 != NULL )
    {
        // Ensure that both entities have physics.
        if( c1->collision->hasPhysics && c2->collision->hasPhysics )
        {
            // Is either object fixed?
            if( c1->collision->fixed || c2->collision->fixed )
            {
                while( true ){ break; }
                printf( "this\n" );
            }
            else
            {
                while( true ){ break; }
                printf( "not this\n" );
            }
        }
    }
}


// Add a references to collision objects where a collision has been observed.
void TW_Collision_AddCollisions( TW_Collision* self, TW_Entity* target )
{
    self->collisionCount += 1;
    if( self->collisionCount > self->collisionBufferSize )
    {
        if( self->collisions == NULL )
        {
            self->collisionBufferSize = self->collisionCount;
            self->collisions = malloc( self->collisionBufferSize * sizeof( TW_Entity* ) );
            self->collisions[ self->collisionCount - 1 ] = target;
        }
        else
        {
            TW_Entity** oldCollisions = self->collisions;
            self->collisions = malloc( self->collisionBufferSize * sizeof( TW_Entity* ) );
            memcpy( self->collisions, oldCollisions, ( self->collisionCount - 1 ) * sizeof( TW_Entity* ) );
            free( oldCollisions );
            self->collisions[ self->collisionCount - 1 ] = target;
        }
    }
}


// Clear all references to collisions.
void TW_Collision_ClearCollisions( TW_Collision* self )
{
    if( self != NULL )
    {
        for( int index = 0; index < self->collisionCount; index++ )
        {
            self->collisions[ index ] = NULL;
        }
        self->collisionCount = 0;
    }
}
