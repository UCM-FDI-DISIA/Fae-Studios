#include "PhysicsComponent.h"
#include "../Src/Manager.h"
PhysicsComponent::PhysicsComponent()
{
}


void PhysicsComponent::initComponent()
{
}

void PhysicsComponent::update()
{
	verticalSpeed += mngr_->getGravityValue();
	if (verticalSpeed > MAX_VERTICAL_SPEED) verticalSpeed = MAX_VERTICAL_SPEED;
	//velocity_ = Vector2D(0, verticalSpeed);
	//cout << velocity_.getX() << endl;
	if (isKnockback) {
		knockbackTimer++;
		if (knockbackTimer > knockbackTime) {
			isKnockback = false;
			knockbackTimer = 0;
		}
	}
}

void PhysicsComponent::knockback()
{
	isKnockback = true;
	velocity_ = velocity_ + Vector2D(-X_KNOCKBACK_FORCE * (knockbackTime - knockbackTimer) / knockbackTime, 0);
}

Vector2D& PhysicsComponent::getVelocity()
{
	return velocity_;
}

PhysicsComponent::~PhysicsComponent()
{
}
