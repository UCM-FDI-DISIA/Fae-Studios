#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
class AttractionComponent : public Component
{
private:
	Entity* player;
	PhysicsComponent* playerPhisics;
	Transform* blackHoleTransform;
	Transform* playerTransform;
	int lifeTime;
	int spawnTime;

public:
	constexpr static ecs::cmpId_type id = ecs::_ATTRACTION;

	AttractionComponent() {	lifeTime = 2000; spawnTime = SDL_GetTicks(); 	}
	void initComponent() override;
	void update() override;
};

