#include "comrade.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

#include "pathfinding.hpp"

Comrade::Comrade(
    Core &core,
    DamageRegistry &damageRegistry,
    BulletSystem &bulletSystem,
    Tilemap &tileset,
    glm::vec2 position
)
: Character(
    core,
    damageRegistry,
    tileset,
    ObjectCreationData{
        .name = "comrade",
        .meshId = "sprite_mesh",
        .colliderId = "friendly_character_collider",
        //.materialId = "comrade_material",
        .transform = Transform2{.position = position}
    },
    *core.resourceManager.getMaterial("comrade_north_material"),
    *core.resourceManager.getMaterial("comrade_south_material"),
    *core.resourceManager.getMaterial("comrade_east_material"),
    *core.resourceManager.getMaterial("comrade_west_material"),
    *core.resourceManager.getMaterial("character_hit_material"),
    *core.resourceManager.getMaterial("comrade_dead1_material"),
    *core.resourceManager.getMaterial("comrade_dead2_material"),
    *core.resourceManager.getSound("death_cry1_sound"),
    *core.resourceManager.getSound("death_cry2_sound"),
    *core.resourceManager.getSound("death_cry3_sound"),
    *core.resourceManager.getSound("death_cry4_sound"),
    *core.resourceManager.getSound("wilhelm_scream1_sound"),
    *core.resourceManager.getSound("wilhelm_scream2_sound"),
    *core.resourceManager.getSound("wilhelm_scream3_sound"),
    *core.resourceManager.getSound("wilhelm_scream4_sound")
)
{
    this->scene = &core.scene;
    this->resourceManager = &core.resourceManager;
    this->tileset = &tileset;
    this->bulletSystem = &bulletSystem;
    this->collision = &core.collision;
}

Comrade::~Comrade()
{
    if (this->body != nullptr)
        this->body->queueFree();
}

void Comrade::update(float deltaTime)
{
    if (this->body == nullptr)
        return;

    this->updateAi(deltaTime);
    this->updateHealth(deltaTime);
    this->updateMovement(deltaTime);
    this->updateAnimation(deltaTime);
}

void Comrade::onDamageApplied()
{
}

void Comrade::onDamageStopped()
{
}

void Comrade::onKilled()
{
}