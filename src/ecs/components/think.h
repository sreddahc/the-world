#pragma once

#include <stdlib.h>

// Type definitions

typedef struct TW_Entity TW_Entity;
typedef struct TW_Component TW_Component;

/**
 * TW_Think - A think component contains a pointer to a function to execute.
 * 
 * Elements:
 * - void       - (*think)( TW_Entity* )    - A pointer to a function to execute
 */
typedef struct TW_Think {
    void (*think)( struct TW_Entity* );
    TW_Component* parent;
} TW_Think;


// Function definitions

/**
 * TW_Think_Create - Create a think object.
 * 
 * The think object must point to a function that takes an entity as an argument.
 * 
 * Args:
 * - void       - *thinkFunction    - Pointer to a function for the think object to run
 * 
 * Returns:
 * - TW_Think*  - The think object with a function tied to it
 */
TW_Think* TW_Think_Create( void *thinkFunction );


/**
 * TW_Think_Run - Run the function in the think object.
 * 
 * Args:
 * TW_Think*        - self          - The think object to free
 */
void TW_Think_Run( TW_Think* self, TW_Entity* entity );


/**
 * TW_Think_Free - Free the resources used by a think object.
 * 
 * Args:
 * TW_Think*        - self          - The think object to free
 */
void TW_Think_Free( TW_Think* self );