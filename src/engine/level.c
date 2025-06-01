#include "level.h"
#include "../ecs/scene.h"
#include "maths.h"


// Create the level object.
TW_Level* TW_Level_Create( TW_Scene* scene, int x, int y )
{
    TW_Level* level = malloc( sizeof( TW_Level ) );
    level->size = TW_Vector2_Create( x, y );
    level->scene = scene;
    return level;
}


// Free the resources used by a level object.
void TW_Level_Free( TW_Level* self )
{
    TW_Vector2_Free( self->size );
    self->scene = NULL;
    free( self );
}


// Set the size of the level object.
void TW_Level_SetSize( TW_Level* self, int x, int y )
{
    TW_Vector2_Set( self->size, x, y );
}


// Set the scene of the level object.
void TW_Level_SetScene( TW_Level* self, TW_Scene* scene )
{
    self->scene = scene;
}


// Return the scene associated with a level.
TW_Scene* TW_Level_GetScene( TW_Level* self )
{
    if( self != NULL )
    {
        return self->scene;
    }
    return NULL;
}


// Checks if a level contains an entity.
bool TW_Level_ContainsEntity( TW_Level* self, TW_Entity* entity, bool checkTexture )
{
    TW_Component* transform = TW_Entity_GetComponent( entity, TW_C_TRANSFORM );
    if( transform != NULL )
    {
        bool check = false;
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        // Must contain either a collision or a texture component to return true.
        if( checkTexture == true )
        {
            x = transform->transform->position->x;
            y = transform->transform->position->y;
            TW_Component* texture = TW_Entity_GetComponent( entity, TW_C_TEXTURE );
            if( texture != NULL )
            {
                check = true;
                w = texture->texture->width;
                h = texture->texture->height;
            }
            else
            {
                TW_Component* text = TW_Entity_GetComponent( entity, TW_C_TEXT );
                if( text != NULL )
                {
                    check = true;
                    w = text->text->texture->width;
                    h = text->text->texture->height;
                }
                else
                {
                    TW_Component* sprite = TW_Entity_GetComponent( entity, TW_C_SPRITE );
                    if( sprite != NULL )
                    {
                        check = true;
                        w = sprite->sprite->width;
                        h = sprite->sprite->height;
                    }
                    else
                    {
                        TW_Component* animation = TW_Entity_GetComponent( entity, TW_C_ANIMATION );
                        if( animation != NULL )
                        {
                            check = true;
                            w = animation->animation->spriteSheet->width;
                            h = animation->animation->spriteSheet->height;
                        }
                    }
                }
            }

        }
        else
        {
            TW_Component* collision = TW_Entity_GetComponent( entity, TW_C_COLLISION );
            if( collision != NULL )
            {
                check = true;
                x = transform->transform->position->x + collision->collision->position->x;
                y = transform->transform->position->y + collision->collision->position->y;
                w = collision->collision->size->x;
                h = collision->collision->size->y;
            }
        }
        if( check == true )
        {
            if( x + w < 0 )
            {
                return true;
            }
            if( y + h < 0 )
            {
                return true;
            }
            if( x > self->size->x )
            {
                return true;
            }
            if( y > self->size->y )
            {
                return true;
            }
        }
    }
    return false;
}
