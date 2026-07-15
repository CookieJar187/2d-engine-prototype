#include "player.h"
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>

void Player::init(Scene& scene, Input& input)
{
    Player::scene = &scene;
    Player::input = &input;
    Player::body = scene.getObjectByName("player");
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
        body->transform.position += velocity;
    }  
}