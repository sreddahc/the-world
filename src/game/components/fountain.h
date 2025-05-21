#pragma once


// Type definitions

typedef struct TW_Scene TW_Scene;
typedef struct TW_Component TW_Component;

enum TW_PowerType {
    TW_PWR_MOON,
    TW_PWR_SUN
};

/**
 * \brief The fountain object
 * 
 * \param parent `TW_Component*` – The parent of this object (if one exists)
 * \param type `enum TW_PowerType` – The type of fountain that this is
 * \param empty `bool` – `true` if the fountain is empty. `false` if full
 * \param cooldown `int` – cooldown in seconds. `0` is no cooldown
 * \param textureEmpty `TW_Component*` – Texture component for an empty foutain
 * \param textureFull `TW_Component*` – Texture component for a full fountain
 */
typedef struct TW_Fountain {
    TW_Component* parent;
    enum TW_PowerType type;
    bool empty;
    int cooldown;
    TW_Component* textureEmpty;
    TW_Component* textureFull;
} TW_Fountain;


// Function definitions

/**
 * \brief Create fountain object.
 * 
 * \returns `TW_Fountain*` – Fountain object initialised
 */
TW_Fountain* TW_Fountain_Create();


/**
 * \brief Free the resources used by a fountain object.
 * 
 * \param self `TW_Fountain*` – Fountain object to free
 */
void TW_Fountain_Free( TW_Fountain* self );


/**
 * \brief Generates a fountain entity of type at x and y position in the target scene.
 * 
 * \param target `TW_Scene*` – Add the fountain entity to this scene
 * \param type `enum TW_PowerType` – The type of fountain to generate
 * \param x `int` – The x position of the fountain (anchor top-left)
 * \param y `int` – The y position of the fountain (anchor top-left)
 */
void TW_Fountain_Generate( TW_Scene* target, enum TW_PowerType type, int x, int y );
