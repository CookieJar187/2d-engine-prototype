#pragma once

#include <iostream>
#include <vector>

#include "object.h"

class ObjectHierarchy
{
private:
    std::vector<std::vector<Object *>> generations;

    uint8_t getGeneration(Object* object);

public:
    ObjectHierarchy();

    void setParent(Object* child, Object* parent);

    void add(Object* object);
    void remove(Object* object);

};