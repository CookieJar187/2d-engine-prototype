#include "object_hierarchy.hpp"

ObjectHierarchy::ObjectHierarchy()
{
    
}

uint8_t ObjectHierarchy::getGeneration(Object* object)
{
    uint8_t generation = 0;
    Object* ancestor = object->getParent();

    while (ancestor != nullptr)
    {
        generation++;
        ancestor = ancestor->getParent();
    }

    return generation;
}

void ObjectHierarchy::setParent(Object* child, Object* parent)
{

}

void ObjectHierarchy::add(Object* object)
{
    uint8_t gen = getGeneration(object);

    if (generations.size() <= gen)
        generations.resize(gen + 1);

    generations[gen].push_back(object);
}

void ObjectHierarchy::remove(Object* object)
{
    uint8_t gen = object->generation;

    std::erase(generations[gen], object);
}