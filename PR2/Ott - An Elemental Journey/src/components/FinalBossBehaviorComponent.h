#pragma once
#include "Transform.h"
#include "MapComponent.h"
class Health;

const int ATTACK_TIME = 5000;
class FinalBossBehaviorComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS;
	FinalBossBehaviorComponent(MapComponent* map);

	void initComponent() override;
	void update() override;

	void deleteBlackHoles();
	void deleteBubbles();
	void deleteSpikes();
private:
	void spawnBubbles();
	void spawnFireWall();
	void spawnFist();
	void spawnFistTop();
	void spawnSpikes();
	void spawnBlackHole();

	Transform* bossTransform;
	Health* bossHealth;
	MapComponent* map_;
	int timeBetweenAttacks;
	int currentElement;
	int FIREWALL_HEIGHT = 400, FIREWALL_WIDTH = 30;
	int FIST_SIZE = 250;

	std::vector<Entity*> blackHoles;
	std::vector<Entity*> bubbles;
	std::vector<Entity*> spikes;
};


