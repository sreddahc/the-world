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
                        for( int j = 0; j < target->collision->collisionCount; j++ )
                        {
                            if( target->collision->collisions[ j ] == entity )
                            {
                                alreadyObserved = true;
                            }
                        }
                        // If it has not, add collision reference to both entities.
                        if( alreadyObserved == false )
                        {
                            // Add collision references to both entities
                            TW_Collision_AddCollisions( self, scene->entities[ index ] );
                            TW_Collision_AddCollisions( target->collision, entity );

                            // Apply physics to both entities
                            TW_Collision_Physics( entity, scene->entities[ index ] );
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
            if( ( c1->collision->fixed || c2->collision->fixed ) && c1->collision->fixed != c2->collision->fixed )
            {
                TW_Entity* eFixed = NULL;
                TW_Component* cFixed = NULL;
                TW_Component* tFixed = NULL;
                TW_Entity* eMove = NULL;
                TW_Component* cMove = NULL;
                TW_Component* tMove = NULL;
                TW_Component* vMove = NULL;

                if( c1->collision->fixed )
                {
                    eFixed = entity1;
                    cFixed = c1;
                    tFixed = t1;
                    eMove = entity2;
                    cMove = c2;
                    tMove = t2;
                }
                else
                {
                    eFixed = entity2;
                    cFixed = c2;
                    tFixed = t2;
                    eMove = entity1;
                    cMove = c1;
                    tMove = t1;
                }
                vMove = TW_Entity_GetComponent( eMove, TW_C_VELOCITY );

                // Establish mid point of each component (now labelled fixed and move)
                float fixedCentreX = (float)cFixed->collision->oldPosition->x + (float)cFixed->collision->position->x + ( (float)cFixed->collision->size->x / 2 );
                float fixedCentreY = (float)cFixed->collision->oldPosition->y + (float)cFixed->collision->position->y + ( (float)cFixed->collision->size->y / 2 );
                
                float moveOldCentreX = (float)cMove->collision->oldPosition->x + (float)cMove->collision->position->x + ( (float)cMove->collision->size->x / 2 );
                float moveOldCentreY = (float)cMove->collision->oldPosition->y + (float)cMove->collision->position->y + ( (float)cMove->collision->size->y / 2 );

                // Establish move entities position relative to fixed entity
                int moveRelDirectionX = 1;
                int moveRelDirectionY = 1;
                
                // (x1,y1) = top-left of fixed entity, (x2, y2) = bottom-right of fixed entity initially
                int innerX1 = tFixed->transform->position->x + cFixed->collision->position->x;
                int innerY1 = tFixed->transform->position->y + cFixed->collision->position->y;
                int innerX2 = innerX1 + cFixed->collision->size->x;
                int innerY2 = innerY1 + cFixed->collision->size->y;

                if( moveOldCentreX <= fixedCentreX )
                {
                    moveRelDirectionX = -1;
                    innerX2 = tMove->transform->position->x + cMove->collision->position->x + cMove->collision->size->x;
                }
                else
                {
                    innerX1 = tMove->transform->position->x + cMove->collision->position->x;
                }
                
                if( moveOldCentreY <= fixedCentreY )
                {
                    moveRelDirectionY = -1;
                    innerY2 = tMove->transform->position->y + cMove->collision->position->y + cMove->collision->size->y;
                }
                else
                {
                    innerY1 = tMove->transform->position->y + cMove->collision->position->y;
                }
                
                // Work out which side of the inner rectangle is bigger
                int xDiff = 0;
                int yDiff = 0;
                if( innerX2 - innerX1 >= innerY2 - innerY1 )
                {
                    // kick in Y direction
                    yDiff = innerY2 - innerY1;
                    int offsetX = TW_Vector2_GetPoint(
                        moveOldCentreX,
                        moveOldCentreY,
                        fixedCentreX,
                        fixedCentreY,
                        TW_AXIS_X,
                        (int)( fixedCentreY + ( ( (float)( cFixed->collision->size->y ) / 2 ) + moveRelDirectionY * yDiff ) )
                    );
                    if( offsetX >= fixedCentreX )
                    {
                        xDiff = offsetX - fixedCentreX;
                    }
                    else
                    {
                        xDiff = fixedCentreX - offsetX;
                    }
                }
                else
                {
                    xDiff = innerX2 - innerX1;
                    int offsetY = TW_Vector2_GetPoint(
                        moveOldCentreX,
                        moveOldCentreY,
                        fixedCentreX,
                        fixedCentreY,
                        TW_AXIS_Y,
                        (int)( fixedCentreX + ( ( (float)( cFixed->collision->size->x ) / 2 ) + moveRelDirectionX * xDiff ) )
                    );
                    if( offsetY >= fixedCentreY )
                    {
                        yDiff = offsetY - fixedCentreY;
                    }
                    else
                    {
                        yDiff = fixedCentreY - offsetY;
                    }
                    
                }

                // Player and Platform logic goes here... for now
                TW_Component* cPlatform = TW_Entity_GetComponent( eFixed, TW_C_PLATFORM );
                TW_Component* cPlayer= TW_Entity_GetComponent( eMove, TW_C_PLAYER );
                if( cPlatform != NULL && cPlayer != NULL )
                {
                    // Check if collision occurred on the floor of the platform.
                    // This can be done better
                    if( moveRelDirectionX == -1 && vMove->velocity->speed->y > 0 )
                    {
                        cPlayer->player->onGround = true;
                        cPlayer->player->jumping = false;
                        vMove->velocity->speed->y = 0;
                    }
                    if( vMove->velocity->speed->y > vMove->velocity->acceleration->y )
                    {
                        cPlayer->player->onGround = false;
                    }
                    if( cPlayer->player->onGround == true )
                    {
                        xDiff = 0;
                        // yDiff = ( tMove->transform->position->y + cMove->transform->position->y + cMove->collision->size->y ) - ( tFixed->transform->position->y + cFixed->collision->position->y );
                        yDiff = 0;
                    }
                //     // elif()
                //     // Bump position and reset speed.
                //     tMove->transform->position->x += ( moveRelDirectionX * xDiff );
                //     tMove->transform->position->y += ( moveRelDirectionY * yDiff );
                //     vMove->velocity->speed->y = 0;
                // }
                // else
                // {
                    // Bump position and reset speed.
                    tMove->transform->position->x += ( moveRelDirectionX * xDiff );
                    tMove->transform->position->y += ( moveRelDirectionY * yDiff );
                    vMove->velocity->speed->y = 0;
                }
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
