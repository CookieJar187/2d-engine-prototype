#include "collision.hpp"

Collision::Collision(World &world) : world(&world) {}

MovementResult Collision::moveAndSlide(Object &moving, const glm::vec2 &movement)
{
    this->collisionSolver.moveAndSlide(moving, movement);
}

std::optional<RaycastHit> Collision::raycast(
    const glm::vec2 &start,
    const glm::vec2 &end,
    const RaycastFilter filter
)
{
    this->raycaster.raycast(start, end, filter);
}