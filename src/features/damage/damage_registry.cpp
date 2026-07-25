#include <iostream>

#include "damage_registry.h"

void DamageRegistry::registerDamageable(Object2 *object, Damageable *damageable)
{
    if (object == nullptr || damageable == nullptr)
        return;

    entries[object] = damageable;
}

void DamageRegistry::unregisterDamageable(Object2 *object)
{
    entries.erase(object);
}

Damageable *DamageRegistry::getDamageable(Object2 *object) const
{
    auto it = entries.find(object);

    if (it == entries.end())
        return nullptr;

    return it->second;
}