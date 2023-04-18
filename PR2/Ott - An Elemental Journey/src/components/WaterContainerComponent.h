#pragma once
#include "../ecs/Component.h"
class WaterContainerComponent :public Component
{
private:
	Entity* fireBoss;
	float fillRate = 0.05f, currentFill = 0;
	int originalHeight, originalYpos;
	
public:
	WaterContainerComponent(Entity* fireBossRef);
	virtual void initComponent();
	virtual void update();
	inline float getCurrentFill() { return currentFill; }
	void dropWater();
	constexpr static ecs::cmpId_type id = ecs::_MAP;
};

