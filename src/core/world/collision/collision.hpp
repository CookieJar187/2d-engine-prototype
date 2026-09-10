#pragma once

#include <optional>

#include "world.hpp"
#include "collision_solver.hpp"
#include "raycaster.hpp"

class Collision{
private:
    World *world;

    CollisionSolver collisionSolver{*world};
    Raycaster raycaster{*world};

public:
    Collision(World &world);

    MovementResult moveAndSlide(Object &moving, const glm::vec2 &movement);

    std::optional<RaycastHit> raycast(
        const glm::vec2 &start,
        const glm::vec2 &end,
        const RaycastFilter filter
    );
};