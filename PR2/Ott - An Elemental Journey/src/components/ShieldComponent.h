#pragma once
#include "../ecs/Component.h"
#include "FramedImage.h"
#include "Health.h"
#include "PhysicsComponent.h"

class ShieldComponent : public Component {
private:
    FramedImageOtt* image_;
    Health* health_;
    PhysicsComponent* physics_;
    bool hasTakenShieldOut;

public:
    constexpr static ecs::cmpId_type id = ecs::_SHIELD;

    ShieldComponent() : Component(), hasTakenShieldOut(false) {}
    void initComponent() override;
    void takeShield();
    void guardShield();
    inline int checkDamage(int damage, bool dir) const { 
        if (physics_->getLookDirection() != dir) return -1;
        else return damage;
    }

    inline bool hasShield() const { return hasTakenShieldOut; }
};

