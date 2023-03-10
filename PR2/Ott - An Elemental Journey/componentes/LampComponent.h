#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include <string>
using namespace std;
class LampComponent : public Component
{
public:
	LampComponent(string n): name(n) {}
	virtual ~LampComponent();
	inline Entity* getConnectedLamp() { return connectedLamp; }
	inline void setConnectedLamp(Entity* e) { connectedLamp = e; }
	constexpr static cmpId_type id = ecs::_MAP;
	string GetName() { return name; }
	void setLampToTeleport(Entity* e) {
		connectedLamp = e;
	}
private:
	Entity* connectedLamp = nullptr;
	string name;
};

