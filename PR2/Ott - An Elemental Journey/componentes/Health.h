#pragma once
#include "Component.h"
class Health : public Component
{
private:
	int maxLife, actualLife;
	ecs::elements elem;
public:
	constexpr static cmpId_type id = ecs::_CTRL;
	Health(int h, ecs::elements e) : Component(), maxLife(2*h), actualLife(2*h), elem(e) {};
	void die();
	bool recieveDamage(ecs::elements elem);
	inline int getHealth() { return actualLife; }
	inline void setElement(int newElem) { 
		switch (newElem)
		{
		case 0: ecs::Light; break;
		case 1: ecs::Earth; break;
		case 2: ecs::Water; break;
		case 3: ecs::Fire; break;
		default: break;
		}
	}
};

