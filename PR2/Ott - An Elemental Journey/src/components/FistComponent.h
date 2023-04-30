#pragma once
#include "../ecs/Entity.h"
#include "../ecs/Component.h"
#include "../components/Transform.h"
class FistComponent : public Component
{
public:
	FistComponent(int side) { 
		side_ = side; 
		if (side_ == 0)dir = { 3,0 };
		else dir = { 0,3 };
	};
	virtual ~FistComponent() {};
	void initComponent() override;
	constexpr static ecs::cmpId_type id = ecs::_FINALBOSS_ATTACK;
private:
	void update() override;
	Transform* player;
	Transform* tr_;
	int initialXPos, initialYPos, maxDistance = 3000;
	int side_ = 0;
	Vector2D dir;
};
