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
	void knockback();
	constexpr static cmpId_type id = ecs::_PHYSICS;
	Vector2D& getVelocity();
private:
	const int MAX_VERTICAL_SPEED = 8;
	const double X_KNOCKBACK_FORCE = 6;
	double knockbackTimer = 0;
	double knockbackTime = 15;
	bool isKnockback = false;
	float verticalSpeed = 0;
	Vector2D velocity_;
};

