#pragma once


// Type definitions

/**
 * TW_Think - A think component contains a pointer to a function to execute.
 * 
 * Elements:
 * - void           - (*think)()    - A pointer to a function to execute when thinking
 */
typedef struct TW_Think {
    void (*think)();
} TW_Think;


// Function definitions

/**
 * TW_Think_Create - Create a think object.
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
void TW_Think_Run( TW_Think* self );


/**
 * TW_Think_Free - Free the resources used by a think object.
 * 
 * Args:
 * TW_Think*        - self          - The think object to free
 */
void TW_Think_Free( TW_Think* self );