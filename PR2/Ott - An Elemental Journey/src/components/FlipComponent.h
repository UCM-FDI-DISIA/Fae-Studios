#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class FlipComponent :  public Component
{
private:
	Transform* transform;

	int lifeTime = 10;
	int spawnTime;

public:
	constexpr static ecs::cmpId_type id = ecs::_FLIP;
	FlipComponent() :Component() { spawnTime = SDL_GetTicks(); };
	virtual ~FlipComponent() {};
	void initComponent() override;

private:
	void update() override;
};

