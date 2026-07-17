#pragma once

#include <vector>

#include "transform2.h"
#include "object2.h"
#include "collision_entry.h"

class CollisionManager {
private:
    bool isColliding(
        const CollisionEntry& entryA,
        const CollisionEntry& entryB
    );
    std::vector<CollisionEntry*> entries;

public:
    void update();
    void registerObject(Object2& obj);
    void unregisterObject(Object2& obj);
    
};