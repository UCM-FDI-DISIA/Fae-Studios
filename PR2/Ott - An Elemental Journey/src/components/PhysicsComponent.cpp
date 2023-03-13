#include "PhysicsComponent.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "CameraComponent.h"

PhysicsComponent::PhysicsComponent() {

}

PhysicsComponent::PhysicsComponent(anims::Colliders c) {
	typeofCollider = c;
}

void PhysicsComponent::initComponent() {

}

void PhysicsComponent::createCollider() {
	auto tr = ent_->getComponent<Transform>();
	colliderOffset = Vector2D(anims::colliders[typeofCollider].izqPixels / (float)anims::colliders[typeofCollider].totalHorPixels * tr->getWidth(),
		anims::colliders[typeofCollider].upPixels / (float)anims::colliders[typeofCollider].totalVertPixels * tr->getHeight());

	colliderWH = Vector2D(anims::colliders[typeofCollider].width / (float)anims::colliders[typeofCollider].totalHorPixels * tr->getWidth(),
		anims::colliders[typeofCollider].height / (float)anims::colliders[typeofCollider].totalVertPixels * tr->getHeight());
}

//void PhysicsComponent::render() {
//	auto cam = mngr_->getCamera()->getComponent<CameraComponent>();
//	auto camera = cam->camera;
//	auto rect = getCollider();
//	rect.x -= camera.x;
//	rect.y -= camera.y;
//
//	sdlutils().images().at("enemy").render(rect);
//}

void PhysicsComponent::update() {
	if (climbing) {
		grounded = true;
		velocity_ = Vector2D(velocity_.getX(), dirClimbing);
	}
	else if (!grounded && gravity) {
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
