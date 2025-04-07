#include "component.h"

// IDK if this does what I want at the moment but I would be interested in knowing if I've done it right.
TW_Component TW_Component_Create( int type, TW_ComponentValue* value ){
    TW_Component* component = malloc( sizeof( component ) );
    component->type = type;
    component->value = value;
    return *component;
}