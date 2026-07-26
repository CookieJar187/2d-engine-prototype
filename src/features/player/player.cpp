#include "player.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

Player::Player(Context &ctx)
{
    this->scene = ctx.scene;
    this->input = ctx.input;
    this->camera = ctx.camera2;
    this->bulletSystem = ctx.bulletSystem;

    ObjectCreationResult result = this->scene->createObject(
        {.name = "player",
         .colliderName = "player",
         .materialName = "player"});

    this->body = result.object;
    characterMotor2.init(*this->body, *ctx.collisionManager, *result.collisionEntry);
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

    if (input->isMouseButtonJustPressed(0))
    {
        glm::vec2 cursorScreen = input->getMousePosition();
        glm::vec2 screenSize = input->getScreenSize();
        glm::vec2 mouseWorld = camera->screenToWorld(cursorScreen, screenSize);

        glm::vec2 origin = this->body->transform.position;
        glm::vec2 direction = glm::normalize(mouseWorld - origin);
        glm::vec2 target = origin + direction * 1000.0f;

        bulletSystem->fire(origin, target, this->body);
    }

    // Camera
    camera->transform.position = glm::mix(
        camera->transform.position,
        Player::body->transform.position,
        0.05f);
}

void Player::die()
{
    std::cout << "Player died" << std::endl;
}

void Player::takeDamage(float amount)
{
    health -= amount;
    std::cout << "Player has taken damage" << std::endl;

    if (health <= 0.0f)
    {
        die();
    }
}