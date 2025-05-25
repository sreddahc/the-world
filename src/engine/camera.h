#pragma once


// Type definitions

typedef struct TW_Entity TW_Entity;
typedef struct TW_Vector2 TW_Vector2;
enum TW_Axis;


/**
 * \brief Camera object
 * 
 * params go here!
 */
typedef struct TW_Camera {
    TW_Entity* target;
    TW_Vector2* size;
} TW_Camera;


// Function definitions

/**
 * \brief Create a camera object.
 * 
 * \param target `TW_Entity*` – The target for the camera to follow. Top-Left of screen if `NULL`.
 * \param x `int` – The width of the screen.
 * \param y `int` – The height of the screen.
 */
void TW_Camera_Create( TW_Entity* target, int x, int y );


/**
 * \brief Frees the resources used by a camera object.
 */
void TW_Camera_Free();


/**
 * \brief Set the target entity for the camera to follow.
 * 
 * \param target `TW_Entity*` – The entity to follow.
 */
void TW_Camera_SetTarget( TW_Entity* target );


/**
 * \brief Set the size of the camera.
 * 
 * \param x `int` – The width of the screen.
 * \param y `int` – The height of the screen.
 */
void TW_Camera_SetSize( int x, int y );


/**
 * Acquire the camera offset.
 * 
 * \param axis `enum TW_Axis` – Specify which axis you require the offset of.
 * 
 * \returns `int` – The offset.
 */
int TW_Camera_GetOffset( enum TW_Axis axis );
