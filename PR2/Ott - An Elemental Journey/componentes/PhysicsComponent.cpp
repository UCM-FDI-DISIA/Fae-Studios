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
	velocity_ = Vector2D(0, verticalSpeed);
	//cout << velocity_.getY() << endl;
}

void PhysicsComponent::collideGround()
{
	verticalSpeed = 0;
	velocity_ = velocity_ * Vector2D(velocity_.getX(), -mngr_->getGravityValue());
}

Vector2D& PhysicsComponent::getVelocity()
{
	return velocity_;
}

PhysicsComponent::~PhysicsComponent()
{
}
