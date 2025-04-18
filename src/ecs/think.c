#include "think.h"


// Create a think object
TW_Think* TW_Think_Create( void *some_function )
{
    TW_Think* thinkObject = malloc( sizeof( TW_Think ) );
    thinkObject->think = some_function;
    return thinkObject;
}


// Run the function in the think object
void TW_Think_Run( TW_Think* self )
{
    self->think();
}


// Free the resources used by a think object
void TW_Think_Free( TW_Think* self )
{
    self->think = 0;  // How do I nullify the think attribute?
    free( self );
}
