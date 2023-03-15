#pragma once
#include "../ecs/Component.h"
#include "PhysicsComponent.h"

class Health;

class EnemyContactDamage : public Component
{
private:
    PhysicsComponent* playerCollider;
    PhysicsComponent* collider;
    Entity* player;
    Health* health_;
public:
    constexpr static ecs::cmpId_type id = ecs::_ENEMYCONTACT;
    EnemyContactDamage() : playerCollider(nullptr), collider(nullptr) {};
    void initComponent() override;
    virtual void update();
};

