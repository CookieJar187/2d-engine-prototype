#include "player.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

Player::Player(Context &ctx)
{
    Player::scene = ctx.scene;
    Player::input = ctx.input;
    Player::camera = ctx.camera2;
    Player::bulletSystem = ctx.bulletSystem;

    ObjectCreationResult result = Player::scene->createObject(
        {.name = "player",
         .colliderName = "player",
         .materialName = "player"});

    Player::body = result.object;
    characterMotor2.init(*Player::body, *ctx.collisionManager, *result.collisionEntry);
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
    {
        glm::vec2 velocity = glm::normalize(inputDirection);
        velocity.x *= MAX_SPEED * deltaTime;
        velocity.y *= MAX_SPEED * deltaTime;
        characterMotor2.moveAndSlide(velocity);
    }

    if (input->isMouseButtonDown() && fired == false)
    {
        glm::vec2 thing = input->getMousePosition();
        bulletSystem->fire(glm::vec2{0, 0}, thing);
        fired = true;
    }

    // Camera
    camera->transform.position = glm::mix(
        camera->transform.position,
        Player::body->transform.position,
        0.05f);
}