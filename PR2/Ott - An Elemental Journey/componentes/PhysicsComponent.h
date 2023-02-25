#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include <iostream>
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();
	virtual void initComponent();
	virtual void update();
	void collideGround();
	constexpr static cmpId_type id = ecs::_PHYSICS;
	Vector2D& getVelocity();
private:
	const int MAX_VERTICAL_SPEED = 8;
	float verticalSpeed = 0;
	Vector2D velocity_;
};

