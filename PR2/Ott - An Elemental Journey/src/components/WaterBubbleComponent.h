#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/Transform.h"

class FinalBossBehaviorComponent;

const int ATTACK_SIZE = 100;

class WaterBubbleComponent : public Component
{
public:
	WaterBubbleComponent(FinalBossBehaviorComponent* bossBehaComp);
	virtual ~WaterBubbleComponent();
	void initComponent() override;
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS_ATTACK;
private:
	void update() override;
	void spawnShot();

	FinalBossBehaviorComponent* bossBehaComp_;
	Entity* player;
	Transform* tr_;
	int timeBetweenShots = 2500, lastTimeShot = 0, lifeTime = 5000, spawnTime;
};