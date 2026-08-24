#include "character.hpp"

#include <iostream>

std::string getCardinalDir(const glm::vec2 &dir)
{
    if (std::abs(dir.x) >= std::abs(dir.y))
        return (dir.x > 0.0f) ? "east" : "west";
    else
        return (dir.y > 0.0f) ? "north" : "south";
}

void Character::updateAnimation(float deltaTime)
{
    if (isDead() || isBeingDamaged())
    {
        return;
    }
    
    std::string cardinal = getCardinalDir(velocity);

    if (cardinal == "north")
        this->body->material = upMaterial;
    if (cardinal == "south")
        this->body->material = downMaterial;
    if (cardinal == "east")
        this->body->material = rightMaterial;
    if (cardinal == "west")
        this->body->material = leftMaterial;
}