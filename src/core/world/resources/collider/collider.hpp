#pragma once

#include <iostream>

#include "aabb_shape.hpp"
#include "collision_group.hpp"

struct Collider
{
    AabbShape *shape = nullptr;
    CollisionGroup *group = nullptr;
};