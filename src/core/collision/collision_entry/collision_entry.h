#pragma once

struct Object2;
struct Transform2;
struct AabbCollider;

struct CollisionEntry
{
    Object2 *object = nullptr;
    Transform2 *tansform = nullptr;
    AabbCollider *collider = nullptr;
};