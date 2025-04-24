#include "../entity.h"


// Create a collision object based on provided parameters.
TW_Collision* TW_Collision_Create( int x, int y, int w, int h )
{
    TW_Collision* collision = malloc( sizeof( TW_Collision ) );

    collision->position = TW_Vector2_Create( x, y );
    collision->size = TW_Vector2_Create( w, h );
    collision->parent = NULL;

    return collision;
}


// Frees the resources used by a collision object.
void TW_Collision_Free( TW_Collision* self )
{
    self->parent = NULL;
    TW_Vector2_Free( self->size );
    TW_Vector2_Free( self->position );
    free( self );
}


// Test whether current entity collides with a target entity
bool TW_Collision_Check( TW_Collision* self, TW_Entity* target )
{
    if( self != NULL )
    {
        if( self->parent != NULL )
        {
            if( self->parent->parent != NULL && target != NULL )
            {
                TW_Entity* currentEntity = self->parent->parent;
                TW_Component* currentTransform = TW_Entity_GetComponent( currentEntity, TW_C_TRANSFORM );
                TW_Component* targetTransform = TW_Entity_GetComponent( target, TW_C_TRANSFORM );
                TW_Component* targetCollision = TW_Entity_GetComponent( target, TW_C_COLLISION );
                if( currentTransform != NULL && targetTransform != NULL && targetCollision != NULL )
                {
                    // !! Currently ignoring anything to do with "Centre" !!

                    // Current dimensions
                    int currentTop = currentTransform->transform->position->y + self->position->y;
                    int currentBot = currentTransform->transform->position->y + self->position->y + self->size->y;
                    int currentLeft = currentTransform->transform->position->x + self->position->x;
                    int currentRight = currentTransform->transform->position->x + self->position->x + self->size->x;
                    
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
        }
    }

    return false;
}