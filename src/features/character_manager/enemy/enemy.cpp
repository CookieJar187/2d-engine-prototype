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
        //.materialId = "enemy_material",
        .transform = Transform2{.position = position}
    },
    *resourceManager.getMaterial("enemy_north_material"),
    *resourceManager.getMaterial("enemy_south_material"),
    *resourceManager.getMaterial("enemy_east_material"),
    *resourceManager.getMaterial("enemy_west_material"),
    *resourceManager.getMaterial("character_hit_material"),
    *resourceManager.getMaterial("enemy_dead1_material"),
    *resourceManager.getMaterial("enemy_dead2_material"),
    *resourceManager.getSound("death_cry1_sound"),
    *resourceManager.getSound("death_cry2_sound"),
    *resourceManager.getSound("death_cry3_sound"),
    *resourceManager.getSound("death_cry4_sound")
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
    this->updateMovement(deltaTime);
    this->updateAnimation(deltaTime);
}

void Enemy::onDamageApplied()
{
}

void Enemy::onDamageStopped()
{
}

void Enemy::onKilled()
{
}