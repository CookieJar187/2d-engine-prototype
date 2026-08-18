#include "enemy.h"

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
{
    this->scene = &scene;
    this->damageRegistry = &damageRegistry;
    this->resourceManager = &resourceManager;
    this->tileset = &tileset;

    this->body = this->scene->createObject({
        .name = "enemy",
        .meshId = "sprite_mesh",
        .colliderId = "character_collider",
        .materialId = "enemy_material",
        .transform = Transform2{.position = glm::vec2(100, -100)}});

    CharacterMotor.init(*this->body, collisionManager);

    this->damageRegistry->registerDamageable(this->body, this);

    std::vector<glm::ivec2> ding = pathfinding::getPathTo(glm::ivec2(1, 1), glm::ivec2(6, 6), tileset);
    for (auto &g : ding)
    {
        std::cout << g.x << ", " << g.y << std::endl;
    }
}

Enemy::~Enemy()
{
    if (this->body != nullptr)
        this->body->queueFree();
}

void Enemy::queueFree() 
{
    queuedForDeletion = true;
}

void Enemy::update(float deltaTime)
{
    if (this->body == nullptr)
        return;

    this->updateDamage(deltaTime);
}