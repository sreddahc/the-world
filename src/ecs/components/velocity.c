#include "../entity.h"


// Create a TW_Velocity object with speed and acceleration. Interacts with a TW_Transform object.
TW_Velocity* TW_Velocity_Create( int xS, int yS, int xA, int yA )
{
    TW_Velocity* velocity = malloc( sizeof( TW_Velocity ) );

    velocity->speed = TW_Vector2_Create( xS, yS );
    velocity->acceleration = TW_Vector2_Create( xA, yA );
    velocity->interval = 100;
    velocity->timeSinceLastInterval = 0.0;
    velocity->parent = NULL;

    return velocity;
}


// Change the speed of a velocity object
void TW_Velocity_SetSpeed( TW_Velocity* self, int x, int y )
{
    self->speed->x = x;
    self->speed->y = y;
}


// Change the speed of a acceleration object
void TW_Velocity_SetAcceleration( TW_Velocity* self, int x, int y )
{
    self->acceleration->x = x;
    self->acceleration->y = y;
}


// Set the interval of a velocity object
void TW_Velocity_SetInterval( TW_Velocity* self, int interval )
{
    self->interval = interval;
}


// Run the velocity object. This should be done every loop as long as the game is not paused.
void TW_Velocity_Run( TW_Velocity* self, TW_Entity* entity )
{
    // A transform component must exist, otherwise the velocity component cannot operate on it.
    TW_Transform* transform = NULL;
    if( entity != NULL )
    {
        TW_Component* transformComponent = TW_Entity_GetComponent( entity, TW_C_TRANSFORM );
        transform = transformComponent->transform;
    }
    if( transform != NULL )
    {
        self->timeSinceLastInterval += TW_GameState_GetDeltaTime();
        if( self->timeSinceLastInterval >= (float)self->interval  / MILLISECONDS_IN_A_SEC )
        {
            // If a collision component exists, update the collision component to track old position
            TW_Collision* collision = NULL;
            TW_Component* collisionComponent = TW_Entity_GetComponent( entity, TW_C_COLLISION );
            collision = collisionComponent->collision;
            if( collision != NULL )
            {
                collision->oldPosition->x = transform->position->x;
                collision->oldPosition->y = transform->position->y;
            }

            self->timeSinceLastInterval -= (float)self->interval  / MILLISECONDS_IN_A_SEC;
            TW_Transform_SetPosition(
                transform,
                transform->position->x + self->speed->x,
                transform->position->y + self->speed->y
            );
            TW_Velocity_SetSpeed(
                self,
                self->speed->x + self->acceleration->x,
                self->speed->y + self->acceleration->y
            );
        }
    }
    else
    {
        printf( "ERROR - TW_Velocity_Run - There is no transform to operate on." );
    }
}


// Frees the resources used by a velocity object
void TW_Velocity_Free( TW_Velocity* self )
{
    self->parent = NULL;
    self->timeSinceLastInterval = 0.0;
    self->interval = 0;
    TW_Vector2_Free( self->acceleration );
    TW_Vector2_Free( self->speed );
    free( self );
}
