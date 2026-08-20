#pragma once

class Damageable
{
public:
    virtual ~Damageable() = default;
    virtual void takeDamage(int amount) = 0;
};