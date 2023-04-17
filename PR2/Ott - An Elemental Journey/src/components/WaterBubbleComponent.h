#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/Transform.h"

const int ATTACK_SIZE = 100;

class WaterBubbleComponent : public Component
{
public:
	WaterBubbleComponent();
	virtual ~WaterBubbleComponent();
	void initComponent() override;
	constexpr static ecs::cmpId_type id = ecs::_WATER_BOSS_ATTACK;
private:
	void update() override;
	void spawnShot();

	Entity* player;
	Transform* tr_;
	int timeBetweenShots = 2500, lastTimeShot = 0, lifeTime = 5 * timeBetweenShots, spawnTime;
};