#include "player.hpp"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

Player::Player(
    Scene &scene,
    Input &input,
    Camera2 &camera,
    CollisionManager &collisionManager,
    ResourceManager &resourceManager,
    BulletSystem &bulletSystem,
    DamageRegistry &damageRegistry,
    Tilemap &tilemap,
    glm::vec2 position
)
: Character(
    scene,
    collisionManager,
    damageRegistry,
    tilemap,
    ObjectCreationData{
        .name = "player",
        .meshId = "sprite_mesh",
        .colliderId = "character_collider",
        //.materialId = "player_material",
        .transform = { .position = position }
    },
    *resourceManager.getMaterial("player_north_material"),
    *resourceManager.getMaterial("player_south_material"),
    *resourceManager.getMaterial("player_east_material"),
    *resourceManager.getMaterial("player_west_material"),
    *resourceManager.getMaterial("character_hit_material"),
    *resourceManager.getMaterial("player_dead1_material"),
    *resourceManager.getMaterial("player_dead2_material")
)
{
    this->input = &input;
    this->camera = &camera;
    this->bulletSystem = &bulletSystem;
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
    if (body == nullptr)
        return;

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

        bulletSystem->fire(origin, direction, body);
    }

    // Camera
    camera->transform.position = glm::mix(
        camera->transform.position,
        body->transform.position,
        0.05f);

    // Character updates
    this->updateHealth(deltaTime);
    this->updateMovement(deltaTime);
    this->updateAnimation(deltaTime);
}