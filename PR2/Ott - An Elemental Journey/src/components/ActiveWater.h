#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "MapComponent.h" 
class ActiveWater :public Component
{
private:
	bool active = false;

public:
	constexpr static ecs::cmpId_type id = ecs::_ACTIVE_WATER;
	ActiveWater(bool act){
		active = act;
	}
	~ActiveWater() {}
	bool getActive() { return active; }
	void setActive(bool act) {
		active = act;
		ent_->setActive(active);
	}
};




