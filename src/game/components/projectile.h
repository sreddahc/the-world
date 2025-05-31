#pragma once


// Type definitions

enum TW_ProjectileType {
    TW_PT_FIREBALL,
    TW_PT_SPELL
};

typedef struct TW_Scene TW_Scene;
typedef struct TW_Entity TW_Entity;
typedef struct TW_Component TW_Component;


/**
 * \brief Basic projectile
 * 
 * \param parent `TW_Component*` – Parent component of the projectile object
 * \param owner `TW_Entity*` – The entity that owns/shot the projectile.
 * \param textureDestroy `TW_Component*` – A reference to the texture component for the destroy animation.
 * \param textureProjectile `TW_Component*` – A reference to the texture component for the projectile animation.
 */
typedef struct TW_Projectile {
    TW_Component* parent;
    TW_Entity* owner;
    enum TW_ProjectileType type;
    TW_Component* textureDestroy;
    TW_Component* textureProjectile;
} TW_Projectile;


// Function definitions

/**
 * \brief Creates a projectile component object.
 * 
 * \returns `TW_Projectile*` – The projectile object initialised.
 */
TW_Projectile* TW_Projectile_Create( TW_Entity* target, enum TW_ProjectileType type );


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
 * \brief Generates a projectile entity and adds it to target scene.
 * 
 * \param target `TW_Entity*` – The entity that's shooting the projectile.
 * \param type `TW_ProjectileType` – The type of projectile.
 */
void TW_Projectile_Generate( TW_Entity* target, enum TW_ProjectileType type );


/**
 * \brief Destroys a projectile entity and removes it from the parent scene.
 * 
 * \param self `TW_Entity*` – The entity to destroy
 */
void TW_Projectile_Destroy( TW_Entity* self );
