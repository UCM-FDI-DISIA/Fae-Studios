#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include <iostream>
#include <SDL.h>
class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	PhysicsComponent(Vector2D offset, Vector2D WidthHeight);
	virtual ~PhysicsComponent();
	virtual void initComponent();
	virtual void update();
	void knockback();
	constexpr static cmpId_type id = ecs::_PHYSICS;
	Vector2D& getVelocity();
	SDL_Rect getCollider() const;
	inline void slowed() { velocity_ = Vector2D(velocity_.getX()/2, velocity_.getY()); }
	inline void lookDirection(bool b) { lookingRight = b; }
	inline bool getLookDirection() { return lookingRight; }
private:
	SDL_Rect collider;
	Vector2D colliderOffset, colliderWH;
	const int MAX_VERTICAL_SPEED = 8;
	const double X_KNOCKBACK_FORCE = 6;
	double knockbackTimer = 0;
	double knockbackTime = 15;
	bool isKnockback = false, lookingRight = true;
	float verticalSpeed = 0;
	Vector2D velocity_;
};

