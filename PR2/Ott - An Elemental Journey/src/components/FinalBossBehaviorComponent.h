#pragma once
#include "Transform.h"
class Health;
class FinalBossBehaviorComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS;
	FinalBossBehaviorComponent(int time);

	void initComponent() override;
	void update() override;
private:
	Health* bossHealth;
	int timeBetweenAttacks, lastAttack;
};


