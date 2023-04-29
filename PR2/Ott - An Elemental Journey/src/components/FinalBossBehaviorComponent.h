#pragma once
#include "Transform.h"
#include "MapComponent.h"
class Health;
class FinalBossBehaviorComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS;
	FinalBossBehaviorComponent(MapComponent* map);

	void initComponent() override;
	void update() override;

private:
	void spawnBubbles();
	void spawnFireWall();
	void spawnFist();

	void spawnBlackHole();

	Transform* bossTransform;
	Health* bossHealth;
	MapComponent* map_;
	int timeBetweenAttacks = 5000, lastAttack = -timeBetweenAttacks;
	int currentElement;
	int BUBBLE_DIM = 70;
	int FIREWALL_HEIGHT = 400, FIREWALL_WIDTH = 30;
	int FIST_SIZE = 200;
	int BLACKHOLE_SIZE = 100;
};


