#include "PhysicsComponent.h"
#include "../Src/Manager.h"
PhysicsComponent::PhysicsComponent() {

}

PhysicsComponent::PhysicsComponent(Vector2D offset = Vector2D(0, 0), Vector2D WidthHeight = Vector2D(0, 0)) {
	colliderOffset = offset;
	colliderWH = WidthHeight;
}

void PhysicsComponent::initComponent() {

}

void PhysicsComponent::update() {
	if (!grounded && gravity) {
		verticalSpeed += mngr_->getGravityValue();
		if (verticalSpeed > MAX_VERTICAL_SPEED) verticalSpeed = MAX_VERTICAL_SPEED;
		velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
		cout << velocity_.getY() << endl;
	}
	
	//cout << velocity_.getX() << endl;
	if (isKnockback) {
		knockbackTimer++;
		if (knockbackTimer > knockbackTime) {
			isKnockback = false;
			knockbackTimer = 0;
		}
	}

	if (abs(velocity_.getY()) > 0.5f) {
		grounded = false;
	}
}

void PhysicsComponent::jump() {
	if (grounded) {
		verticalSpeed = jumpForce;
		velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
	}
}

void PhysicsComponent::knockback() {
	isKnockback = true;
	velocity_ = velocity_ + Vector2D(-X_KNOCKBACK_FORCE * (knockbackTime - knockbackTimer) / knockbackTime, 0);
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
		SDL_Rect collider = { (t->getPos().getX() + colliderOffset.getX()), (t->getPos().getY() + colliderOffset.getY()),
								colliderWH.getX(), colliderWH.getY() };
		return collider;
	}
}
