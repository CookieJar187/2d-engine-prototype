#include "character.hpp"

Character::Character(
    Core &core,
    DamageRegistry &damageRegistry,
    Tilemap &tilemap,
    ObjectCreationData objectCreationData,
    Material &upMaterial,
    Material &downMaterial,
    Material &rightMaterial,
    Material &leftMaterial,
    Material &hitMaterial,
    Material &dead1Material,
    Material &dead2Material,
    Sound &death1Sound,
    Sound &death2Sound,
    Sound &death3Sound,
    Sound &death4Sound,
    Sound &death5Sound,
    Sound &death6Sound,
    Sound &death7Sound,
    Sound &death8Sound
)
{
    this->body = core.scene.createObject(objectCreationData);
    this->body->material = &downMaterial;

    characterMotor.init(*this->body, core.collisionManager);

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

    this->death1Sound = &death1Sound;
    this->death2Sound = &death2Sound;
    this->death3Sound = &death3Sound;
    this->death4Sound = &death4Sound;
    this->death5Sound = &death5Sound;
    this->death6Sound = &death6Sound;
    this->death7Sound = &death7Sound;
    this->death8Sound = &death8Sound;
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