#pragma once
#include "../ecs/Component.h"
#include "Transform.h" 
#include "PhysicsComponent.h"
#include "Acceleration.h"

class Pivot : public Component
{
private:
	Entity* player;
	Entity* map;
	Transform* transform;
	Transform* playerTransform;
	PhysicsComponent* bossPhysics;
	PhysicsComponent* physics;
	bool active = false;
	int num = 0;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSSACCELERATION;
	Pivot(Entity* ent, int n, Entity* map_) {
		player = ent;
		map = map_;
		playerTransform = player->getComponent<Transform>();
		bossPhysics = player->getComponent<PhysicsComponent>();
		num = n;
	}
	~Pivot() {}
	void initComponent() override;
	void update() override;
};



