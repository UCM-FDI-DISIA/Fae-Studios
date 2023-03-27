#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "Health.h"

class WaterBossAttack : public Component
{
private:
	Entity* ott;
	Transform* ottTransform;
	Health* ottHealth;

	Transform* transform;

public:
	constexpr static ecs::cmpId_type id = ecs::_WATER_BOSS_ATTACK;
	WaterBossAttack() {}
	~WaterBossAttack() {}
	void initComponent() override;
	void update() override;
};

