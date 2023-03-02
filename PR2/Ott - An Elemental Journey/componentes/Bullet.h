#pragma once
#include "PhysicsComponent.h"
class Bullet : public Component
{
private:
	Entity* player;
	ecs::elements elem;
	PhysicsComponent* physics;
public:
	constexpr static cmpId_type id = ecs::_BULLET;
	Bullet(Entity* p, ecs::elements e) : Component(), player(p), elem(e), physics(nullptr) {};
	void initComponent() override;
	void update() override;
};

