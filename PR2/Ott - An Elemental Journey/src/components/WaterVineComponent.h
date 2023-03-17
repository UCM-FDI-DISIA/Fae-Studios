#pragma once
#include "../ecs/Component.h"
class WaterVineComponent :public Component
{
private:
	void pickSpawnLocation();
	int originalHeight;
	Entity* waterTankRef;
public:
	WaterVineComponent(Entity* waterTank);
	virtual void initComponent();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_MAP;
};

