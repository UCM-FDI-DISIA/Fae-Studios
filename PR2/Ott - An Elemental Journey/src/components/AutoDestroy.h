#pragma once
#include "../ecs/Component.h"
#include <SDL.h>
class AutoDestroy : public Component
{
private:
	int startCountDown;
	float time;
public:
	AutoDestroy(float t) : time(t), startCountDown(SDL_GetTicks()) {}
	virtual ~AutoDestroy();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_MANAGEMENT;
};

