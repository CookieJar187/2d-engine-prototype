#include "enemy.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

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

    std::vector<glm::ivec2> thing = this->tileset->pathfind(glm::vec2(100, -100), glm::vec2(600, -600));
    for (auto &v : thing)
    {
        std::cout << v.x << ", " << v.y << std::endl;
    }
}

void Enemy::update(float deltaTime)
{
    if (this->body == nullptr)
        return;

    this->updateDamage(deltaTime);
}