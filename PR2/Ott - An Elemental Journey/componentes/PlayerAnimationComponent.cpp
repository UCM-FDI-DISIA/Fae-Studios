#include "PlayerAnimationComponent.h"
#include "PhysicsComponent.h"
#include "../Src/Entity.h"
PlayerAnimationComponent::PlayerAnimationComponent()
{
}

PlayerAnimationComponent::~PlayerAnimationComponent()
{
}

void PlayerAnimationComponent::update()
{
	if (currentAnimation == ATTACK) return;
	Vector2D vel = ent_->getComponent<PhysicsComponent>()->getVelocity();
	if (vel.getY() == 0) {
		if (vel.getX() != 0) currentAnimation = RUN;
		else currentAnimation = IDLE;
	}
	else if (vel.getY() < 0) currentAnimation = JUMP_UP;
	else currentAnimation = FALL;
}

void PlayerAnimationComponent::endAnim()
{
	if (currentAnimation == ATTACK) {

		currentAnimation = IDLE;
	}
}
