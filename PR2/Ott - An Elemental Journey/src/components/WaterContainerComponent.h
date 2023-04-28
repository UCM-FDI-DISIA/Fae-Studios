#pragma once
#include "../ecs/Component.h"
class WaterContainerComponent :public Component
{
private:
	float fillRate = 0.08f, currentFill = 0;
	int originalHeight, originalYpos;
	class Transform* tr;
public:
	WaterContainerComponent();
	virtual void initComponent();
	virtual void update();
	inline float getCurrentFill() { return currentFill; }
	void dropWater();
	constexpr static ecs::cmpId_type id = ecs::_MAP;
};


