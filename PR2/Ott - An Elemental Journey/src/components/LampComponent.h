#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
class LampComponent : public Component
{
public:
	LampComponent(Entity* e);
	virtual ~LampComponent();
	inline Entity* getConnectedLamp() { return connectedLamp; }
	constexpr static cmpId_type id = ecs::_MAP;
private:
	Entity* connectedLamp;
};

