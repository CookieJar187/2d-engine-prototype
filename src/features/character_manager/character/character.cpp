#include "character.hpp"

Character::Character(
    Scene &scene,
    CollisionManager &collisionManager,
    DamageRegistry &damageRegistry,
    Tilemap &tilemap,
    ObjectCreationData objectCreationData,
    Material &upMaterial,
    Material &downMaterial,
    Material &rightMaterial,
    Material &leftMaterial,
    Material &hitMaterial,
    Material &dead1Material,
    Material &dead2Material
)
{
    this->body = scene.createObject(objectCreationData);
    this->body->material = &downMaterial;

    characterMotor.init(*this->body, collisionManager);

    damageRegistry.registerDamageable(this->body, this);

    this->tilemap = &tilemap;
    this->damageRegistry = &damageRegistry;

    this->upMaterial = &upMaterial;
    this->downMaterial = &downMaterial;
    this->rightMaterial = &rightMaterial;
    this->leftMaterial = &leftMaterial;
    this->hitMaterial = &hitMaterial;
    this->dead1Material = &dead1Material;
    this->dead2Material = &dead2Material;
}

Character::~Character()
{
    this->damageRegistry->unregisterDamageable(this->body);

    if (this->body != nullptr)
        this->body->queueFree();
}

void Character::queueFree() 
{
    queuedForDeletion = true;
}

bool Character::isDead() const
{
    return dead;
}

bool Character::isBeingDamaged() const
{
    return damageEffect;
}