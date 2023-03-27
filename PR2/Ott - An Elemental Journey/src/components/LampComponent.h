#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class LampComponent : public Component
{
public:
	LampComponent(Entity* e, int myRoom) : connectedLamp(e), myRoom(myRoom) {}
	virtual ~LampComponent() = default;
	inline Entity* getConnectedLamp() { return connectedLamp; }
	constexpr static ecs::cmpId_type id = ecs::_MAP;
	inline int getRoom() { return myRoom; }
private:
	int myRoom;
	Entity* connectedLamp;
};

