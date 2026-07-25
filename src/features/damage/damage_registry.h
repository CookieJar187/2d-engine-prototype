#pragma once

#include "object2.h"
#include "damageable.h"

class DamageRegistry
{
public:
    void registerDamageable(Object2 *object, Damageable *damageable);

    void unregisterDamageable(Object2 *object);

    Damageable *getDamageable(Object2 *object) const;

private:
    std::unordered_map<Object2 *, Damageable *> entries;
};