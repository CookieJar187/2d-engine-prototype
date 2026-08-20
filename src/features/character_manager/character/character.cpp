#include "character.hpp"

Character::Character(
    Scene &scene,
    CollisionManager &collisionManager,
    DamageRegistry &damageRegistry,
    Tilemap &tilemap,
    ObjectCreationData objectCreationData
)
{
    this->body = scene.createObject(objectCreationData);

    characterMotor.init(*this->body, collisionManager);

    damageRegistry.registerDamageable(this->body, this);

    this->tilemap = &tilemap;
}

Character::~Character()
{
    if (this->body != nullptr)
        this->body->queueFree();
}

void Character::queueFree() 
{
    queuedForDeletion = true;
}

void Character::update(float deltaTime)
{
    if (this->body == nullptr)
        return;

    this->updateHealth(deltaTime);
    this->updateMovement(deltaTime);
}