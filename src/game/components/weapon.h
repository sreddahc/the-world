#pragma once


// Type definitions

enum TW_WeaponType {
    TW_WT_PUNCH,
    TW_WT_SWORD
};


typedef struct TW_Scene TW_Scene;
typedef struct TW_Entity TW_Entity;
typedef struct TW_Component TW_Component;


/**
 * \brief A weapon object
 * 
 * \param parent `TW_Component*` – The parent component of this object.
 * \param type `enum TW_WeaponType` – The type of weapon.
 * \param owner `TW_Entity*` – The target entity that owns the weapon object.
 */
typedef struct TW_Weapon {
    TW_Component* parent;
    enum TW_WeaponType type;
    TW_Entity* owner;
} TW_Weapon;


// Function definitions

/**
 * \brief Create a weapon object.
 * 
 * \returns `TW_Weapon*` - The weapon object initialised.
 */
TW_Weapon* TW_Weapon_Create( TW_Entity* target, enum TW_WeaponType type );


/**
 * \brief Frees the resources used by a weapon object.
 * 
 * \param self `TW_Weapon*` – Weapon object to free
 */
void TW_Weapon_Free( TW_Weapon* self );


/**
 * \brief The think object for a weapon object.
 * 
 * \param self `TW_Entity*` – The entity of the think object.
 */
void TW_Weapon_Think( TW_Entity* self );


/**
 * \brief Generates a weapon entity and adds it to the scene of target entity.
 * 
 * \param target `TW_Entity*` – The target for the weapon to be created on.
 * \param type `enum TW_WeaponType` – The weapon type to add.
 */
void TW_Weapon_Generate( TW_Entity* target, enum TW_WeaponType type );
