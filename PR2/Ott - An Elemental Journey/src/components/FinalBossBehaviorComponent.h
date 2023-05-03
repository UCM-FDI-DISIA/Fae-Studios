#pragma once
#include "Transform.h"
#include "MapComponent.h"
class Health;

const int ATTACK_TIME = 5000;
const int STUNNED_TIME = 3000;
const int CURE_TIME = 1000;
class FinalBossBehaviorComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS;
	FinalBossBehaviorComponent(MapComponent* map);
	~FinalBossBehaviorComponent() { deleteWeakPoints(); }
	void initComponent() override;
	void update() override;

	void deleteBlackHoles();
	void deleteBubbles();
	void deleteSpikes();
	void deleteSpikeFromVec(Entity* spikes);
	void deleteWeakPoints();
private:
	void spawnBubbles();
	void spawnFireWall();
	void spawnFist();
	void spawnFistTop();
	void spawnSpikes();
	void spawnBlackHole();
	void spawnWeakPoints();

	Transform* bossTransform;
	Health* bossHealth;
	MapComponent* map_;
	int timeBetweenAttacks;
	int timeStunned;
	int timeCure;
	int currentElement;
	int FIREWALL_HEIGHT = 400, FIREWALL_WIDTH = 30;
	int FIST_SIZE = 250;
	int lastElem;
	bool stunned, isWeakPoints;
	std::vector<Entity*> blackHoles;
	std::vector<Entity*> bubbles;
	std::vector<Entity*> spikes;
	std::vector<Entity*> weakPoints;
};


