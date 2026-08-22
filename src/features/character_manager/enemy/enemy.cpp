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
    Tilemap &tileset
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
        .transform = Transform2{.position = glm::vec2(100, -100)}
    }
)
{
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

    this->updateHealth(deltaTime);
    this->updateMovement(deltaTime);
}

void Enemy::onDamageApplied()
{
    std::cout << "enemy damaged\n";
    body->material->texture = this->resourceManager->getTexture("enemy_hit_texture");
}

void Enemy::onDamageStopped()
{
    std::cout << "enemy stopped\n";
    body->material->texture = this->resourceManager->getTexture("enemy_texture");
}

void Enemy::onKilled()
{
    std::cout << "enemy killed\n";
}