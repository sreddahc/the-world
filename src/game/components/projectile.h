#pragma once


// Type definitions

typedef struct TW_Scene TW_Scene;
typedef struct TW_Entity TW_Entity;
typedef struct TW_Component TW_Component;


/**
 * \brief Basic projectile
 * 
 * \param parent `TW_Component*` – Parent component of the projectile object
 */
typedef struct TW_Projectile {
    TW_Component* parent;
    TW_Component* textureImpact;
    TW_Component* textureShoot;
} TW_Projectile;


// Function definitions

/**
 * \brief Creates a projectile component object.
 * 
 * \returns `TW_Projectile*` – The projectile object initialised.
 */
TW_Projectile* TW_Projectile_Create();


/**
 * \brief Frees the resources used by a projectile component.
 * 
 * \param self `TW_Projectile*` – The projectile object to free.
 */
void TW_Projectile_Free( TW_Projectile* self );


/**
 * \brief The think function for a projectile entity.
 * 
 * \param entity `TW_Entity*` – The entity the think function belongs to
 */
void TW_Projectile_Think( TW_Entity* entity );


/**
 * \brief Generates a projectile entity and adds it to target scene
 * 
 * \param scene `TW_Scene*` – The scene to add the projectile entity to
 * \param caster `TW_Entity*` – The entity that's shooting the projectile
 */
void TW_Projectile_Generate( TW_Scene* scene, TW_Entity* caster );


/**
 * \brief Destroys a projectile entity and removes it from the parent scene.
 * 
 * \param self `TW_Entity*` – The entity to destroy
 */
void TW_Projectile_Destroy( TW_Entity* self );
