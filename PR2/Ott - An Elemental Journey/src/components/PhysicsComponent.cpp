#include "PhysicsComponent.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"

PhysicsComponent::PhysicsComponent() {

}

PhysicsComponent::PhysicsComponent(Vector2D offset = Vector2D(0, 0), Vector2D WidthHeight = Vector2D(0, 0)) {
	colliderOffset = offset;
	colliderWH = WidthHeight;
}

void PhysicsComponent::initComponent() {

}

void PhysicsComponent::update() {
	if (climbing) {
		grounded = true;
		// mngr_->desactivateGravity();
		velocity_ = Vector2D(velocity_.getX(), dirClimbing);
	}
	else if (!grounded) {
		// mngr_->activateGravity();
		verticalSpeed += mngr_->getGravityValue();
		if (verticalSpeed > MAX_VERTICAL_SPEED) verticalSpeed = MAX_VERTICAL_SPEED;
		velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
	}

	if (isKnockback) {
		knockbackTimer++;
		if (knockbackTimer > knockbackTime) {
			isKnockback = false;
			knockbackTimer = 0;
		}
	}

	if (!climbing && abs(velocity_.getY()) > 0.5f) {
		grounded = false;
	}
}

void PhysicsComponent::jump() {
	if (grounded && !climbing) {
		verticalSpeed = jumpForce;
		velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
	}
}

void PhysicsComponent::knockback() {
	isKnockback = true;
	int kckbDir = 1;
	if (lookingRight) kckbDir = -1;
	velocity_ = velocity_ + Vector2D(kckbDir * X_KNOCKBACK_FORCE * (knockbackTime - knockbackTimer) / knockbackTime, 0);
}

Vector2D& PhysicsComponent::getVelocity() {
	return velocity_;
}

PhysicsComponent::~PhysicsComponent()
{
}

SDL_Rect PhysicsComponent::getCollider() const {
	if (ent_->hasComponent<Transform>()) {
		Transform* t = ent_->getComponent<Transform>();
		SDL_Rect collider = { (t->getPosition().getX() + colliderOffset.getX()), (t->getPosition().getY() + colliderOffset.getY()),
								colliderWH.getX(), colliderWH.getY() };
		return collider;
	}
}
