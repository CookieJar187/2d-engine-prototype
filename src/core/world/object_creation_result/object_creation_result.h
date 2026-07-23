#pragma once

struct Object2;
struct CollisionEntry;

struct ObjectCreationResult
{
    Object2 *object = nullptr;
    CollisionEntry *collisionEntry = nullptr;
};