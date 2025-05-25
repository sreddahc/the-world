#pragma once


// Type definitions

typedef struct TW_Vector2 TW_Vector2;
typedef struct TW_Scene TW_Scene;


/**
 * \brief Level object.
 * 
 * \param size `TW_Vector2*` – The size of the level.
 * \param scene `TW_Scene*` – The scene for the level. 
 */
typedef struct TW_Level {
    TW_Vector2* size;
    TW_Scene* scene;
} TW_Level;


// Function definitions

/**
 * \brief Create the level object.
 * 
 * \param scene `TW_Scene*` – The scene associated with the level
 * \param x `int` – The width of the level.
 * \param y `int` – The height of the level.
 * 
 * \returns `TW_Level*` – An initialised level object.
 */

 TW_Level* TW_Level_Create( TW_Scene* scene, int x, int y );


/**
 * \brief Free the resources used by a level object.
 * 
 * \param self `TW_Level*` – The level object to free.
 * 
 * \note Does not free the seen associated with the level.
 */
 void TW_Level_Free( TW_Level* self );


 /**
  * \brief Set the size of the level object.
  * 
  * \param self `TW_Level*` – The level object to set.
  * \param x `int` – The width of the level.
  * \param y `int` – The height of the level.
  */
 void TW_Level_SetSize( TW_Level* self, int x, int y );


 /**
  * \brief Set the scene of the level object.
  * 
  * \param self `TW_Level*` - Set the scene of this level.
  * \param scene `TW_Scene*` – The scene to set for the level.
  */
void TW_Level_SetScene( TW_Level* self, TW_Scene* scene );


/**
 * \brief Return the scene associated with a level.
 * 
 * \param self `TW_Level*` – The level to return a scene from.
 * 
 * \returns `TW_Scene*` – The level's scene.
 */
TW_Scene* TW_Level_GetScene( TW_Level* self );

//  void TW_Level_LoadFromFile( char* file );