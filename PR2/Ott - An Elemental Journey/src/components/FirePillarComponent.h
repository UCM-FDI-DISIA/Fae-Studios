
#pragma once
#include "PhysicsComponent.h"
#include "Transform.h"

class FirePillarComponent : public Component
{
private:
    Transform* tr;
    int startVerticalPos, countDown = -1, timeActivated = 6;
    float speed = 2;
    
public:
    constexpr static ecs::cmpId_type id = ecs::_MAP;
    FirePillarComponent();
    void initComponent() override;
    virtual void update();
};
