#include "component.h"


// Creates a pointer to a component of specified type and value
TW_Component* TW_Component_Create( int type, TW_Component_Value* value ){
    TW_Component* component = malloc( sizeof( TW_Component ) );
    component->type = type;
    component->value = value;
    return component;
}
