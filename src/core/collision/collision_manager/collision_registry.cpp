#include <iostream>

#include "collision_manager.h"

CollisionEntry *CollisionManager::registerObject(Object2 &obj)
{
    if (obj.collider == nullptr)
        return {};

    CollisionEntry *newEntry = new CollisionEntry();
    newEntry->object = &obj;
    newEntry->collider = obj.collider;
    newEntry->tansform = &obj.transform;

    try
    {
        entries.push_back(newEntry);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return newEntry;
}

void CollisionManager::unregisterObject(Object2 &obj)
{
}