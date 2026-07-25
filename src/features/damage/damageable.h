#pragma once

class Damageable
{
public:
    virtual ~Damageable() = default;
    virtual void takeDamage(float amount) = 0;
};