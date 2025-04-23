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


void TW_Collision_GetRelativePosition( TW_Collision* self, TW_Entity* target )
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
                    // Maths to determine if a collision occurred goes here.
                    
                }
            }
        }
    }
}