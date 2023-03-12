#include "PhysicsComponent.h"
#include "../Src/Manager.h"
PhysicsComponent::PhysicsComponent() {
	jumpForce = earthJumpForce;
}

PhysicsComponent::PhysicsComponent(Vector2D offset = Vector2D(0, 0), Vector2D WidthHeight = Vector2D(0, 0)) {
	colliderOffset = offset;
	colliderWH = WidthHeight;
	jumpForce = earthJumpForce;
}

void PhysicsComponent::initComponent() {

}

void PhysicsComponent::update() {
	//ascenso progresivo en el agua cuando tiene otros elementos
	if (!floating && inWater && ent_->getComponent<Health>()->getElement() != ecs::Water)
	{
		//ajustes velocidad vertical cuando entra por arriba/lados
		if (verticalSpeed > 0) { verticalSpeed = 0.0; } 
		verticalSpeed += -0.01; if (verticalSpeed < -1.5) { verticalSpeed = -1.5; }
		velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
		return;
	}
	if (climbing) {
		grounded = true;
		mngr_->desactivateGravity();
		velocity_ =  Vector2D(velocity_.getX(),dirClimbing);
	}
	else if (!grounded) {
		mngr_->activateGravity();
	}

	if (!grounded && gravity && (!inWater || (inWater && ent_->getComponent<Health>()->getElement() == ecs::Water))) {
		
		if (inWater) 
		{
			verticalSpeed +=0.1;
		}
		else
		{
			verticalSpeed += mngr_->getGravityValue();
		}
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
	
	if (inWater || floating) { jumpForce = waterJumpForce; }
	else { jumpForce = earthJumpForce; }
	//condiciones de salto: que este flotamdo o que este en el suelo no escalando y o bien no este en el agua o bien lo este pero sea de elemento de agua
	if (floating||(grounded && !climbing && ((!inWater) || (inWater && ent_->getComponent<Health>()->getElement() == ecs::Water)))) {
		verticalSpeed = jumpForce;
		velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
	}
}

void PhysicsComponent::knockback() {
	isKnockback = true;
	int kckbDir = 1;
	if (lookingRight) kckbDir = -1;
	velocity_ = velocity_ + Vector2D(kckbDir* X_KNOCKBACK_FORCE * (knockbackTime - knockbackTimer) / knockbackTime, 0);
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
