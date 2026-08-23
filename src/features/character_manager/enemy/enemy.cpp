#include "enemy.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

#include "pathfinding.hpp"

Enemy::Enemy(
    Scene &scene,
    DamageRegistry &damageRegistry,
    CollisionManager &collisionManager,
    ResourceManager &resourceManager,
    Tilemap &tileset,
    glm::vec2 position
)
: Character(
    scene,
    collisionManager,
    damageRegistry,
    tileset,
    ObjectCreationData{
        .name = "enemy",
        .meshId = "sprite_mesh",
        .colliderId = "character_collider",
        .materialId = "enemy_material",
        .transform = Transform2{.position = position}
    }
)
{
    this->scene = &scene;
    this->resourceManager = &resourceManager;
    this->tileset = &tileset;
}

Enemy::~Enemy()
{
    if (this->body != nullptr)
        this->body->queueFree();
}

void Enemy::update(float deltaTime)
{
    if (this->body == nullptr)
        return;

    this->updateAi(deltaTime);
    this->updateHealth(deltaTime);
}

void Enemy::onDamageApplied()
{
    body->material = this->resourceManager->getMaterial("enemy_hit_material");
}

void Enemy::onDamageStopped()
{
    body->material = this->resourceManager->getMaterial("enemy_material");
}

void Enemy::onKilled()
{
}