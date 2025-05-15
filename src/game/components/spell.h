#pragma once


// Type definitions

typedef struct TW_Scene TW_Scene;
typedef struct TW_Entity TW_Entity;
typedef struct TW_Component TW_Component;


/**
 * \brief Basic spell
 * 
 * \param parent `TW_Component*` – Parent component of the spell object
 */
typedef struct TW_Spell {
    TW_Component* parent;
    TW_Component* textureImpact;
    TW_Component* textureShoot;
} TW_Spell;


// Function definitions

/**
 * \brief Creates a spell component object.
 * 
 * \returns `TW_Spell*` – The spell object initialised.
 */
TW_Spell* TW_Spell_Create();


/**
 * \brief Frees the resources used by a spell component.
 * 
 * \param self `TW_Spell*` – The spell object to free.
 */
void TW_Spell_Free( TW_Spell* self );


/**
 * \brief The think function for a spell entity.
 * 
 * \param entity `TW_Entity*` – The entity the think function belongs to
 */
void TW_Spell_Think( TW_Entity* entity );


/**
 * \brief Generates a spell entity and adds it to target scene
 * 
 * \param scene `TW_Scene*` – The scene to add the spell entity to
 * \param caster `TW_Entity*` – The entity that's shooting the spell
 */
void TW_Spell_GenerateSpell( TW_Scene* scene, TW_Entity* caster );


/**
 * \brief Destroys a spell entity and removes it from the parent scene.
 * 
 * \param self `TW_Entity*` – The entity to destroy
 */
void TW_Spell_DestroySpell( TW_Entity* self );