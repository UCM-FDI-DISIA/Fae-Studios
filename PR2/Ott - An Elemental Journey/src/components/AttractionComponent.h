#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class FinalBossBehaviorComponent;

class AttractionComponent : public Component
{
private:
	Entity* player;
	PhysicsComponent* playerPhisics;
	Transform* playerTransform;
	Transform* blackHoleTransform;
	FinalBossBehaviorComponent* bossBehaComp_;
	int lifeTime;
	int spawnTime;
	bool active = false;

public:
	constexpr static ecs::cmpId_type id = ecs::_ATTRACTION;

	AttractionComponent(FinalBossBehaviorComponent* bossBehaComp) :Component(), bossBehaComp_(bossBehaComp) { lifeTime = 5000; spawnTime = SDL_GetTicks(); }
	void initComponent() override;
	void update() override;
};

