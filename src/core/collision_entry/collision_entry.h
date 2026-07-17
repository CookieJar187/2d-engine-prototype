#pragma once

#include "object2.h"
#include "transform2.h"
#include "collider.h"

struct CollisionEntry
{
    Object2* object;
    Transform2* tansform;
    AabbCollider* collider;

    /*
    CollisionEntry(
        Object2* object = nullptr,
        Transform2* tansform = nullptr,
        AabbCollider* collider = nullptr
    ) : object(object), transform(transform), collider(collider) {}
     */
};