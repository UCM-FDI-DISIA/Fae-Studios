#pragma once
#include "../ecs/Component.h"
#include "FramedImage.h"
class BlackHoleAnimationComp : public Component
{
private:
	FramedImage* image;

	int spawnTime;
	int frameTime;

public:
	constexpr static ecs::cmpId_type id = ecs::_BLACK_HOLE_ANIMATION;

	BlackHoleAnimationComp() : Component() { frameTime = 50; spawnTime = SDL_GetTicks(); }
	void initComponent() override;
	void update() override;
};

