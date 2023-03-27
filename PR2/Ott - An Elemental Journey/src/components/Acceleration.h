#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
class Acceleration : public Component
{
private:
	Entity* player;
	Transform* transform;
	Transform* playerTransform;
	PhysicsComponent* physics;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSS_PIVOT;
	Acceleration() {}
	~Acceleration() {}
	void initComponent() override;
	void update() override;
};

