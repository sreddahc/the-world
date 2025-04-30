#include "../scene.h"


// Create a collision object based on provided parameters.
TW_Collision* TW_Collision_Create( int x, int y, int w, int h )
{
    TW_Collision* collision = malloc( sizeof( TW_Collision ) );

    collision->position = TW_Vector2_Create( x, y );
    collision->centre = TW_Vector2_Create( 0, 0 );
    collision->size = TW_Vector2_Create( w, h );
    collision->oldPosition = TW_Vector2_Create( 0, 0 );
    collision->solid = false;
    collision->parent = NULL;
    collision->collisionCount = 0;
    collision->collisionBufferSize = 0;

    return collision;
}


// Frees the resources used by a collision object.
void TW_Collision_Free( TW_Collision* self )
{
    self->collisionBufferSize = 0;
    self->collisionCount = 0;
    self->parent = NULL;
    self->solid = false;
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
                    // Stops the compiler erroring -- remove when ready to add code
                    while( true )
                    {
                        break;
                    }
                }
            }
        }
    }
}


// TW_Collision