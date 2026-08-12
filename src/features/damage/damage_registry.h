#pragma once

#include "object.h"
#include "damageable.h"

class DamageRegistry
{
public:
    void registerDamageable(Object *object, Damageable *damageable);

    void unregisterDamageable(Object *object);

    Damageable *getDamageable(Object *object) const;

private:
    std::unordered_map<Object *, Damageable *> entries;
};