#pragma once
#include "../ecs/Component.h"
class waterDropComponent : public Component
{
private:
	int startTime, lifeTime = 1000;
	float fallSpeed = 0, maxSpeed = 7, acceleration = 0.1;
	class Transform* tr;
public:
	waterDropComponent();
	virtual void initComponent();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_MAP;
};

