#include "player.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

Player::Player(
    Core &core,
    DamageRegistry &damageRegistry,
    BulletSystem &bulletSystem,
    Tilemap &tilemap,
    GrenadeSystem &grenadeSystem,
    MeleeSystem &meleeSystem,
    CameraShaker &cameraShaker,
    glm::vec2 position
)
: Character(
    core,
    damageRegistry,
    tilemap,
    ObjectCreationData{
        .name = "player",
        .meshId = "sprite_mesh",
        .colliderId = "friendly_character_collider",
        //.materialId = "player_material",
        .transform = { .position = position }
    },
    *core.resourceManager.getMaterial("player_north_material"),
    *core.resourceManager.getMaterial("player_south_material"),
    *core.resourceManager.getMaterial("player_east_material"),
    *core.resourceManager.getMaterial("player_west_material"),
    *core.resourceManager.getMaterial("character_hit_material"),
    *core.resourceManager.getMaterial("player_dead1_material"),
    *core.resourceManager.getMaterial("player_dead2_material"),
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
    this->input = &core.input;
    this->camera = &core.camera;
    this->bulletSystem = &bulletSystem;
    this->grenadeSystem = &grenadeSystem;
    this->meleeSystem = &meleeSystem;
    this->cameraShaker = &cameraShaker;
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
    if (body == nullptr)
        return;

    // Camera
    camera->transform.position = glm::mix(
        camera->transform.position,
        body->transform.position,
        0.05f);

    if (!(isDead() || isBeingDamaged()))
    {
        glm::vec2 inputDirection(0, 0);

        if (input->isKeyDown(65))
            inputDirection.x -= 1;
        else if (input->isKeyDown(68))
            inputDirection.x += 1;

        if (input->isKeyDown(83))
            inputDirection.y -= 1;
        else if (input->isKeyDown(87))
            inputDirection.y += 1;

        if (!glm::all(glm::epsilonEqual(inputDirection, glm::vec2(0.0f), 0.0001f)))
            moveTo(inputDirection, deltaTime);

        if (input->isMouseButtonJustPressed(0))
        {
            glm::vec2 cursorScreen = input->getMousePosition();
            glm::vec2 screenSize = input->getScreenSize();
            glm::vec2 mouseWorld = camera->screenToWorld(cursorScreen, screenSize);

            glm::vec2 origin = body->transform.position;
            glm::vec2 direction = glm::normalize(mouseWorld - origin);
            glm::vec2 target = origin + direction * 1000.0f;

            bulletSystem->fire(origin, direction, BulletTeam::Friendly);

            cameraShaker->gunShake();
        }

        if (input->isKeyJustPressed(71))
        {
            glm::vec2 cursorScreen = input->getMousePosition();
            glm::vec2 screenSize = input->getScreenSize();
            glm::vec2 mouseWorld = camera->screenToWorld(cursorScreen, screenSize);

            glm::vec2 origin = body->transform.position;
            glm::vec2 direction = glm::normalize(mouseWorld - origin);

            grenadeSystem->launch(origin, direction);
        }

        if (input->isKeyJustPressed(32))
        {
            meleeSystem->newMelee(this->body->transform.position, *this->body);
        }
    }

    // Character updates
    this->updateHealth(deltaTime);
    this->updateMovement(deltaTime);
    this->updateAnimation(deltaTime);
}