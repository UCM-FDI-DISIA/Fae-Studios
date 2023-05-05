#pragma once
#include "Transform.h"
#include "MapComponent.h"
#include "FinalBossAnimation.h"
class Health;

const int ATTACK_TIME = 5000;
const int STUNNED_TIME = 5000;
const int CURE_TIME = 3000;
class FinalBossBehaviorComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS;
	FinalBossBehaviorComponent(MapComponent* map);
	~FinalBossBehaviorComponent();
	void initComponent() override;
	void update() override;
	void reset();

	void deleteBlackHoles();
	void deleteBubbles();
	void deleteBubbleFromVec(Entity* bubble);
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
	FinalBossAnimation* bossAnim;
	Entity* player;

	int timeBetweenAttacks;
	int timeStunned;
	int timeCure;
	int currentElement;
	int FIREWALL_HEIGHT = 600, FIREWALL_WIDTH = 90;
	int FIST_SIZE = 250;
	int lastElem;

	int numAttacks = 0;
	bool stunned, isWeakPoints, waitingForReset;
	std::vector<Entity*> blackHoles;
	std::vector<Entity*> bubbles;
	std::vector<Entity*> spikes;
	std::vector<Entity*> weakPoints;
	std::list<Entity*> fists;
};


