#pragma once
#include "Transform.h"
class Health;
class FinalBossBehaviorComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS;
	FinalBossBehaviorComponent();

	void initComponent() override;
	void update() override;
private:
	void spawnBubbles();
	void spawnFireWall();
	Health* bossHealth;
	int timeBetweenAttacks = 5000, lastAttack = -timeBetweenAttacks;
	int currentElement;
	int BUBBLE_DIM = 70;
	int FIREWALL_HEIGHT = 400, FIREWALL_WIDTH = 30;
};


