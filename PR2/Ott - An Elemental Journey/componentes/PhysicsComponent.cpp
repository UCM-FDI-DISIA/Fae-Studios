#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
}


void PhysicsComponent::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
}

void PhysicsComponent::update()
{
	verticalSpeed += mngr_->getGravityValue();
	if (verticalSpeed > MAX_VERTICAL_SPEED) verticalSpeed = MAX_VERTICAL_SPEED;
	Vector2D& gravity = tr_->getVel();
	gravity = Vector2D(gravity.getX(), verticalSpeed);
}

void PhysicsComponent::collideGround()
{
	verticalSpeed = 0;
	Vector2D& gravity = tr_->getVel();
	gravity = Vector2D(gravity.getX(), -mngr_->getGravityValue());
}

PhysicsComponent::~PhysicsComponent()
{
}
