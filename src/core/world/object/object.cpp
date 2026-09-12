#include <iostream>

#include "object.h"

Object *Object::getParent() const
{
    return parent;
}

void Object::setParent(Object *newParent)
{
    requestedParent = newParent;
    parentChangeQueued = true;
}

void Object::queueFree()
{
    queuedForDeletion = true;
}