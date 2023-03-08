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
	PhysicsComponent(Vector2D vel) : velocity_(vel) {}
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
	inline void setGrounded(bool value) { grounded = value; if (grounded) verticalSpeed = 0; }
	inline bool isGrounded() { return grounded; }
	inline void setVelocity(Vector2D value) { velocity_ = value; }
	inline void setGravity(bool g) { gravity = g; }
	void jump();
private:
	SDL_Rect collider;
	Vector2D colliderOffset, colliderWH;
	const int MAX_VERTICAL_SPEED = 8;
	const double X_KNOCKBACK_FORCE = 6;
	double knockbackTimer = 0;
	double knockbackTime = 15;
	bool isKnockback = false, lookingRight = true, grounded = false, gravity = true;
	float verticalSpeed = 0;
	Vector2D velocity_;

	const int jumpForce = -10;
};

