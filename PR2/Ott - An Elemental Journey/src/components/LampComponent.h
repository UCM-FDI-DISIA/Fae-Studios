#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class LampComponent : public Component
{
public:
	LampComponent(Entity* e) : connectedLamp(e) {}
	virtual ~LampComponent() = default;
	inline Entity* getConnectedLamp() { return connectedLamp; }
	constexpr static ecs::cmpId_type id = ecs::_MAP;
private:
	Entity* connectedLamp;
};

