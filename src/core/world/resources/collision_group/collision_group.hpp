#pragma once

#include <iostream>

using CollisionGroupId = uint8_t;
using CollisionMask = uint16_t;

struct CollisionGroup
{
    CollisionGroupId id = 0;
    CollisionMask collidesWith = 0;
};