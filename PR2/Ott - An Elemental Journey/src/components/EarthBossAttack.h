#pragma once
#include "../ecs/Component.h"
#include "PhysicsComponent.h"
#include "Transform.h"
#include "EnemyAttack.h"
#include "GrowVine.h"
#include <vector>

//brainstorm literal porque no se como hacerlo jeje
class EarthBossAttack : public Component
{
private:
	Entity* player = nullptr;
	Transform* tr_ = nullptr;
	PhysicsComponent* playerCollider_ = nullptr;

public:
	constexpr static ecs::cmpId_type id = ecs::_ATTACK;
	EarthBossAttack() {};

	void attack();
	void initComponent() override;
	void update() override;
};
