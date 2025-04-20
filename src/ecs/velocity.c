#include "velocity.h"


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


// Run the velocity object. This should be done every loop as long as the game is not paused.
void TW_Velocity_Run( TW_Velocity* self, TW_Component* transform )
{

}


// Change the speed of a velocity object
void TW_Velocity_SetSpeed( TW_Velocity* self, int x, int y )
{

}


// Change the speed of a acceleration object
void TW_Velocity_SetAcceleration( TW_Velocity* self, int x, int y )
{

}


// Set the interval of a velocity object
void TW_Velocity_SetInterval( TW_Velocity* self, int interval )
{
    
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
