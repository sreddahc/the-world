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
    collision->collisionSize = 0;
    collision->collisionMax = 0;
    collision->collisions = NULL;

    return collision;
}


// Frees the resources used by a collision object.
void TW_Collision_Free( TW_Collision* self )
{
    for( int index = 0; index < self->collisionMax; index++ )
    {
        self->collisions[ index ] = NULL;
    }
    free( self->collisions );
    self->collisionMax = 0;
    self->collisionSize = 0;
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
                        // Check if collision has already been resolved.
                        bool alreadyObserved = false;
                        for( int j = 0; j < target->collision->collisionSize; j++ )
                        {
                            if( target->collision->collisions[ j ] == entity )
                            {
                                alreadyObserved = true;
                            }
                        }
                        // If not, add collision references for both collision components.
                        if( alreadyObserved == false )
                        {
                            TW_Collision_AddCollisions( self, scene->entities[ index ] );
                            TW_Collision_AddCollisions( target->collision, entity );

                            // Attempt to resolve physics for both components
                            TW_Collision_Resolve( entity, scene->entities[ index ] );
                        }
                    }
                }
            }
        }
        // Update old position of collision with new position.
        TW_Component* transform = TW_Entity_GetComponent( entity, TW_C_TRANSFORM );
        if( transform != NULL )
        {
            collision->collision->oldPosition->x = transform->transform->position->x;
            collision->collision->oldPosition->y = transform->transform->position->y;
        }
    }
}


// NOTE: This function replaces TW_Collisions_Physics()
// Attempt to resolve the physics of 2 entities which have physics.
void TW_Collision_Resolve( TW_Entity* eA, TW_Entity* eB )
{
    // Get required components
    TW_Component* cA = TW_Entity_GetComponent( eA, TW_C_COLLISION );
    TW_Component* tA = TW_Entity_GetComponent( eA, TW_C_TRANSFORM );
    TW_Component* cB = TW_Entity_GetComponent( eB, TW_C_COLLISION );
    TW_Component* tB = TW_Entity_GetComponent( eB, TW_C_TRANSFORM );

    // Ensure all required components exist
    if( cA != NULL && tA != NULL && cB != NULL && tB != NULL )
    {
        // Get required components
        TW_Component* vA = TW_Entity_GetComponent( eA, TW_C_VELOCITY );
        TW_Component* vB = TW_Entity_GetComponent( eB, TW_C_VELOCITY );

        // Both entities must have physics
        if( ( cA->collision->hasPhysics == true ) && ( cB->collision->hasPhysics == true ) )
        {
            // At least one entity must have velocity and not be fixed
            if( ( vA != NULL && cA->collision->fixed == false ) || ( vB != NULL && cB->collision->fixed == false ) )
            {
                // Calculate the direction for each entity
                float dirAx = 0.0;
                float dirAy = 0.0;
                float dirBx = 0.0;
                float dirBy = 0.0;
                dirAx = (float)( tA->transform->position->x - cA->collision->oldPosition->x );
                dirAy = (float)( tA->transform->position->y - cA->collision->oldPosition->y );
                dirBx = (float)( tB->transform->position->x - cB->collision->oldPosition->x );
                dirBy = (float)( tB->transform->position->y - cB->collision->oldPosition->y );

                // Determine side of collision
                enum TW_Direction sideA = 0;
                enum TW_Direction sideB = 0;

                // X Axis
                if( dirAx != 0 || dirBx != 0 )
                {
                    // Both entities are moving left (one may be static)
                    if( dirAx <= 0 && dirBx <= 0 )
                    {
                        if( dirAx < dirBx ) // <B <<A or B <<A
                        {
                            sideA |= TW_DIR_LEFT;
                            sideB |= TW_DIR_RIGHT;
                        }
                        else // <A <<B or A <<B
                        {
                            sideA |= TW_DIR_RIGHT;
                            sideB |= TW_DIR_LEFT;
                        }
                    }
                    // Both entities are moving right (one may be static)
                    else if( dirAx >= 0 && dirBx >= 0 )
                    {
                        if( dirAx > dirBx ) // A>> B> or A>> B
                        {
                            sideA |= TW_DIR_RIGHT;
                            sideB |= TW_DIR_LEFT;
                        }
                        else // B>> A> or B>> A
                        {
                            sideA |= TW_DIR_LEFT;
                            sideB |= TW_DIR_RIGHT;
                        }
                    }
                    // Entities are moving towards each other
                    else
                    {
                        if( dirAx < 0 ) // B> <A
                        {
                            sideA |= TW_DIR_LEFT;
                            sideB |= TW_DIR_RIGHT;
                        }
                        else // A> <B
                        {
                            sideA |= TW_DIR_RIGHT;
                            sideB |= TW_DIR_LEFT;
                        }
                    }
                }

                // Y Axis
                if( dirAy != 0 || dirBy != 0 )
                {
                    // Both entities are moving up (one may be static)
                    if( dirAy <= 0 && dirBy <= 0 )
                    {
                        if( dirAy < dirBy ) //  ^B
                        {                   // ^^A
                            sideA |= TW_DIR_UP;
                            sideB |= TW_DIR_DOWN;
                        }
                        else    //  ^A
                        {       // ^^B
                            sideA |= TW_DIR_DOWN;
                            sideB |= TW_DIR_UP;
                        }
                    }
                    // Both entities are moving down (one may be static)
                    else if( dirAy >= 0 && dirBy >= 0 )
                    {
                        if( dirAy > dirBy ) // vvA
                        {                   // vB
                            sideA |= TW_DIR_DOWN;
                            sideB |= TW_DIR_UP;
                        }
                        else    // vvB
                        {       //  vA
                            sideA |= TW_DIR_UP;
                            sideB |= TW_DIR_DOWN;
                        }
                    }
                    // Both entities are moving towards each other
                    else
                    {
                        if( dirAy < 0 ) // vB
                        {               // ^A
                            sideA |= TW_DIR_UP;
                            sideB |= TW_DIR_DOWN;
                        }
                        else            // vA
                        {               // ^B
                            sideA |= TW_DIR_DOWN;
                            sideB |= TW_DIR_UP;
                        }
                    }
                }

                // Points of the sides of collision
                int Ax = 0;
                int Ay = 0;
                int Bx = 0;
                int By = 0;
                if( ( sideA & TW_DIR_RIGHT ) == TW_DIR_RIGHT )
                {
                    Ax = cA->collision->oldPosition->x + cA->collision->position->x + cA->collision->size->x;
                    Bx = cB->collision->oldPosition->x + cB->collision->position->x;    // Inferred
                }
                else if ( ( sideA & TW_DIR_LEFT ) == TW_DIR_LEFT )
                {
                    Ax = cA->collision->oldPosition->x + cA->collision->position->x;
                    Bx = cB->collision->oldPosition->x + cB->collision->position->x + cB->collision->size->x; // Inferred
                }

                if( ( sideA & TW_DIR_DOWN ) == TW_DIR_DOWN )
                {
                    Ay = cA->collision->oldPosition->y + cA->collision->position->y + cA->collision->size->y;
                    By = cB->collision->oldPosition->y + cB->collision->position->y;    // Inferred
                }
                else if( ( sideA & TW_DIR_UP ) == TW_DIR_UP )
                {
                    Ay = cA->collision->oldPosition->y + cA->collision->position->y;
                    By = cB->collision->oldPosition->y + cB->collision->position->y + cB->collision->size->y; // Inferred
                }

                // Time of collision
                float time = 0.0;
                if( dirAx - dirBx != 0 )
                {
                    float newTime = (float)( Bx - Ax ) / (float)( dirAx - dirBx );
                    if( newTime > time )
                    {
                        time = newTime;
                    }
                }
                if( dirBx - dirAx != 0 )
                {
                    float newTime = (float)( Ax - Bx ) / (float)( dirBx - dirAx );
                    if( newTime > time )
                    {
                        time = newTime;
                    }
                }
                if( dirAy - dirBy != 0 )
                {
                    float newTime = (float)( By - Ay ) / (float)( dirAy - dirBy );
                    if( newTime > time )
                    {
                        time = newTime;
                    }
                }
                if( dirBy - dirAy != 0 )
                {
                    float newTime = (float)( Ay - By ) / (float)( dirBy - dirAy );
                    if( newTime > time )
                    {
                        time = newTime;
                    }
                }

                // Establish exact side of collision for each of A and B
                enum TW_Direction collisionSideA = sideA;
                enum TW_Direction collisionSideB = sideB;
                int inner1X = TW_M_Max( tA->transform->position->x + cA->collision->position->x, tB->transform->position->x + cB->collision->position->x );
                int inner1Y = TW_M_Max( tA->transform->position->y + cA->collision->position->y, tB->transform->position->y + cB->collision->position->y );
                int inner2X = TW_M_Min( tA->transform->position->x + cA->collision->position->x + cA->collision->size->x, tB->transform->position->x + cB->collision->position->x + cB->collision->size->x);
                int inner2Y = TW_M_Min( tA->transform->position->y + cA->collision->position->y + cA->collision->size->y, tB->transform->position->y + cB->collision->position->y + cB->collision->size->y);
                if( abs( inner2X - inner1X ) > abs( inner2Y - inner1Y ) )
                {
                    collisionSideA &= ( TW_DIR_UP | TW_DIR_DOWN );
                    collisionSideB &= ( TW_DIR_UP | TW_DIR_DOWN );
                }
                else
                {
                    collisionSideA &= ( TW_DIR_LEFT | TW_DIR_RIGHT );
                    collisionSideB &= ( TW_DIR_LEFT | TW_DIR_RIGHT );
                }

                // Calculate new position of each object at time
                float moveAx = (float)tA->transform->position->x;
                float moveAy = (float)tA->transform->position->y;
                float moveBx = (float)tB->transform->position->x;
                float moveBy = (float)tB->transform->position->y;
                if( cA->collision->fixed == false )
                {
                    if( sideA & ( TW_DIR_LEFT | TW_DIR_RIGHT ) )
                    {
                        moveAx = (float)cA->collision->oldPosition->x + dirAx * time;
                    }
                    if( sideA & ( TW_DIR_UP | TW_DIR_DOWN ) )
                    {
                        moveAy = (float)cA->collision->oldPosition->y + dirAy * time;
                    }
                }
                if( cB->collision->fixed == false )
                {
                    if( sideB & ( TW_DIR_LEFT | TW_DIR_RIGHT ) )
                    {
                        moveBx = (float)cB->collision->oldPosition->x + dirBx * time;
                    }
                    if( sideB & ( TW_DIR_UP | TW_DIR_DOWN ) )
                    {
                        moveBy = (float)cB->collision->oldPosition->y + dirBy * time;
                    }
                }

                // Update positions
                tA->transform->position->x = (int)moveAx;
                tA->transform->position->y = (int)moveAy;
                tB->transform->position->x = (int)moveBx;
                tB->transform->position->y = (int)moveBy;

                // Reset gravity
                if( ( sideA & ( TW_DIR_DOWN | TW_DIR_UP ) ) && cA->collision->fixed == false && vA != NULL )
                {
                    vA->velocity->speed->y = 0;
                }
                if( ( sideB & ( TW_DIR_DOWN | TW_DIR_UP ) ) && cB->collision->fixed == false && vB != NULL )
                {
                    vB->velocity->speed->y = 0;
                }
                
                // Reset horizontal speed if a wall is hit
                if( ( sideA & ( TW_DIR_LEFT | TW_DIR_RIGHT ) ) && cA->collision->fixed == false && vA != NULL && !( sideA & TW_DIR_DOWN ) )
                {
                    vA->velocity->speed->x = 0;
                }
                if( ( sideB & ( TW_DIR_LEFT | TW_DIR_RIGHT ) ) && cB->collision->fixed == false && vB != NULL && !( sideB & TW_DIR_DOWN ) )
                {
                    vB->velocity->speed->x = 0;
                }

            }
        }
    }
}


// Add a references to collision objects where a collision has been observed.
void TW_Collision_AddCollisions( TW_Collision* self, TW_Entity* target )
{
    self->collisionSize += 1;
    if( self->collisionSize > 0 )
    {
        if( self->collisionSize > self->collisionMax )
        {
            self->collisionMax = self->collisionSize;
            if( self->collisions == NULL )
            {
                self->collisions = malloc( self->collisionMax * sizeof( TW_Entity* ) );
            }
            else
            {
                TW_Entity** oldCollisions = self->collisions;
                self->collisions = malloc( self->collisionMax * sizeof( TW_Entity* ) );
                memcpy( self->collisions, oldCollisions, ( self->collisionSize - 1 ) * sizeof( TW_Entity* ) );
                free( oldCollisions );
            }
        }
        self->collisions[ self->collisionSize - 1 ] = target;
    }
}


// Clear all references to collisions.
void TW_Collision_ClearCollisions( TW_Collision* self )
{
    if( self != NULL )
    {
        for( int index = 0; index < self->collisionSize; index++ )
        {
            self->collisions[ index ] = NULL;
        }
        self->collisionSize = 0;
    }
}
