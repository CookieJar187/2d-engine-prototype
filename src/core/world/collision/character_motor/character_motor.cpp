#include "character_motor.h"

void CharacterMotor::init(Object &object, CollisionManager &collisionManager)
{
    CharacterMotor::object = &object;
    CharacterMotor::collisionManager = &collisionManager;
}

MovementResult CharacterMotor::moveAndSlide(const glm::vec2 &movement)
{
    return collisionManager->moveAndSlide(*this->object, movement);
}