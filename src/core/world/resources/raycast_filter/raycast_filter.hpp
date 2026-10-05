#pragma once

enum class RaycastFilterMode
{
    Ignore,
    PermitOnly
};

struct RaycastFilter
{
private:
    CollisionMask groups = 0;
    RaycastFilterMode mode = RaycastFilterMode::Ignore;

public:
    void setGroup(const CollisionGroup *group)
    { this->groups = (1u << group->id); }

    void setMode(const RaycastFilterMode mode)
    { this->mode = mode; }

    friend class Raycaster;
};
