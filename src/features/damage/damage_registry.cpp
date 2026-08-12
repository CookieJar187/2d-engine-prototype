#include <iostream>

#include "damage_registry.h"

void DamageRegistry::registerDamageable(Object *object, Damageable *damageable)
{
    if (object == nullptr || damageable == nullptr)
        return;

    entries[object] = damageable;
}

void DamageRegistry::unregisterDamageable(Object *object)
{
    entries.erase(object);
}

Damageable *DamageRegistry::getDamageable(Object *object) const
{
    auto it = entries.find(object);

    if (it == entries.end())
        return nullptr;

    return it->second;
}