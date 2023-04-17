#include "PhysicsComponent.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "CameraComponent.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"
#include "Health.h"

const float gravityValue = 0.2;


PhysicsComponent::PhysicsComponent() {
	jumpForce = earthJumpForce;
}

PhysicsComponent::PhysicsComponent(colliders::Colliders c) {
	typeofCollider = c;
	jumpForce = earthJumpForce;
}

void PhysicsComponent::initComponent() {

}

void PhysicsComponent::createCollider() {
	auto tr = ent_->getComponent<Transform>();
	colliderOffset = Vector2D(colliders::collider[typeofCollider].izqPixels / (float)colliders::collider[typeofCollider].totalHorPixels * tr->getWidth(),
		colliders::collider[typeofCollider].upPixels / (float)colliders::collider[typeofCollider].totalVertPixels * tr->getHeight());

	colliderWH = Vector2D(colliders::collider[typeofCollider].width / (float)colliders::collider[typeofCollider].totalHorPixels * tr->getWidth(),
		colliders::collider[typeofCollider].height / (float)colliders::collider[typeofCollider].totalVertPixels * tr->getHeight());
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
	if (!stopped) {
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
			velocity_ = Vector2D(velocity_.getX(), dirClimbing);
		}
		if (!grounded && gravity && (!inWater || (inWater && ent_->getComponent<Health>()->getElement() == ecs::Water))) {

			if (inWater)
			{
				if ((!floating || floating && verticalSpeed > 0)|| ent_->getComponent<Health>()->getElement() == ecs::Water)
				{
					verticalSpeed += 0.1;
				}
			}
			else
			{
				verticalSpeed += gravityValue;
			}
			if (verticalSpeed > MAX_VERTICAL_SPEED) verticalSpeed = MAX_VERTICAL_SPEED;
			velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
		}

		if (isKnockback) {
			knockbackTimer++;
			if (knockbackTimer > knockbackTime) {
				isKnockback = false;
				knockbackTimer = 0;
				velocity_ = Vector2D(0, velocity_.getY());
			}
		}

		if (!climbing && abs(velocity_.getY()) > 0.5f) {
			grounded = false;
		}
	}
	else setVelocity(Vector2D(0, 0));

}

void PhysicsComponent::jump() {
	if (!stopped) {
		if (inWater || floating) { jumpForce = waterJumpForce; }
		else { jumpForce = earthJumpForce; }
		//condiciones de salto: que este flotamdo o que este en el suelo no escalando y o bien no este en el agua o bien lo este pero sea de elemento de agua
		if (floating || (grounded && !climbing && ((!inWater) || (inWater && ent_->getComponent<Health>()->getElement() == ecs::Water)))) {
			verticalSpeed = jumpForce;
			velocity_ = Vector2D(velocity_.getX(), verticalSpeed);
		}
	}
}

void PhysicsComponent::knockback(bool dir) {
	if (!stopped) {
		isKnockback = true;

		int kckbDir = 1;
		if (!dir) kckbDir = -1;
		velocity_ = velocity_ + Vector2D(kckbDir * X_KNOCKBACK_FORCE, 0);
	}
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
		SDL_Rect collider = { (int)(t->getPosition().getX() + colliderOffset.getX()), (int)(t->getPosition().getY() + colliderOffset.getY()),
                              (int)(colliders::collider[typeofCollider].width / (float)colliders::collider[typeofCollider].totalHorPixels * t->getWidth()),
			(int)(colliders::collider[typeofCollider].height / (float)colliders::collider[typeofCollider].totalVertPixels * t->getHeight()) };
		return collider;
	}
}
