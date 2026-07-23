#include "player.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

#include "aabb_collider.h"

void Player::init(Scene &scene, Input &input, CollisionManager &collisionManager)
{
    Player::scene = &scene;
    Player::input = &input;

    ObjectCreationResult result = scene.createObject("player", AabbCollider{glm::vec2(50, 50)});

    body = result.object;
    characterMotor2.init(*Player::body, collisionManager, *result.collisionEntry);
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
        velocity.x *= maxSpeed * deltaTime;
        velocity.y *= maxSpeed * deltaTime;
        characterMotor2.moveAndSlide(velocity);
    }
}