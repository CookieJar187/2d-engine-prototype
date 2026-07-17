#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "collision_manager.h"
#include "object2.h"

bool CollisionManager::isColliding(
    const CollisionEntry& entryA,
    const CollisionEntry& entryB
) {

    if (
        entryA.collider == nullptr ||
        entryA.tansform == nullptr ||
        entryB.collider == nullptr ||
        entryB.tansform == nullptr
    )
    {
        return false;
    }
    
    const glm::vec2 minA = entryA.tansform->position - entryA.collider->halfSize;
    const glm::vec2 maxA = entryA.tansform->position + entryA.collider->halfSize;

    const glm::vec2 minB = entryB.tansform->position - entryB.collider->halfSize;
    const glm::vec2 maxB = entryB.tansform->position + entryB.collider->halfSize;

    return
        minA.x <= maxB.x &&
        maxA.x >= minB.x &&
        minA.y <= maxB.y &&
        maxA.y >= minB.y;
}

void CollisionManager::update()
{
    
    for (std::size_t i = 0; i < entries.size(); ++i)
    {
        for (std::size_t j = i + 1; j < entries.size(); ++j)
        {
            CollisionEntry* entryA = entries[i];
            CollisionEntry* entryB = entries[j];

            if (entryA == nullptr || entryB == nullptr)
                continue;

            if (isColliding(*entryA, *entryB))
            {
                std::cout << "There is a collision!" << std::endl;
            }
        }
    }
}

void CollisionManager::registerObject(Object2& obj)
{
    if (!obj.collider.has_value())
        return;
    
    CollisionEntry* newEntry = new CollisionEntry();
    newEntry->object = &obj;
    newEntry->collider = &obj.collider.value();
    newEntry->tansform = &obj.transform;
    
    try{
        entries.push_back(newEntry);
    }
    catch (const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
    }
}

void CollisionManager::unregisterObject(Object2& obj)
{
    
}