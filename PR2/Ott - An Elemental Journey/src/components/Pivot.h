#pragma once
#include "../ecs/Component.h"
#include "Transform.h" 
#include "PhysicsComponent.h"

class Pivot : public Component
{
private:
	Entity* player;
	Transform* transform;
	Transform* playerTransform;
	PhysicsComponent* bossPhysics;
	PhysicsComponent* physics;
	bool active = false;
	int num = 0;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSSACCELERATION;
	Pivot(Entity* ent, int n) {
		player = ent;
		playerTransform = player->getComponent<Transform>();
		bossPhysics = player->getComponent<PhysicsComponent>();
		num = n;
	}
	~Pivot() {}
	void initComponent() override;
	void update() override;
};



