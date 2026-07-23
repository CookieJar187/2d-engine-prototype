#include "character_motor2.h"

void CharacterMotor2::init(Object2 &object, CollisionManager &collisionManager, CollisionEntry &entry)
{
    CharacterMotor2::object = &object;
    CharacterMotor2::collisionManager = &collisionManager;
    CharacterMotor2::collisionEntry = &entry;
}

MovementResult CharacterMotor2::moveAndSlide(const glm::vec2 &movement)
{
    return collisionManager->moveAndSlide(*collisionEntry, movement);
}