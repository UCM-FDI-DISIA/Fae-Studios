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

	void deleteBlackHoles();
	void deleteBubbles();

private:
	void spawnBubbles();
	void spawnFireWall();
	void spawnFist();

	void spawnBlackHole();

	Transform* bossTransform;
	Health* bossHealth;
	MapComponent* map_;
	int timeBetweenAttacks = 8000, lastAttack = -timeBetweenAttacks;
	int currentElement;
	int FIREWALL_HEIGHT = 400, FIREWALL_WIDTH = 30;
	int FIST_SIZE = 200;

	std::vector<Entity*> blackHoles;
	std::vector<Entity*> bubbles;
};


