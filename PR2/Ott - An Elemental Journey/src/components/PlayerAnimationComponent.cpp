#include "PlayerAnimationComponent.h"
#include "PhysicsComponent.h"
#include "Health.h"
#include "../ecs/Entity.h"
#pragma once

void PlayerAnimationComponent::update()
{
	if (currentAnimation == ATTACK || currentAnimation == VANISH || currentAnimation == DIE) return;
	Vector2D vel = ent_->getComponent<PhysicsComponent>()->getVelocity();
	if (vel.getY() == 0) {
		if (vel.getX() != 0) currentAnimation = RUN;
		else currentAnimation = IDLE;
	}
	else if (vel.getY() < 0) currentAnimation = JUMP_UP;
	else currentAnimation = FALL;
	if (invincible && SDL_GetTicks() - damageTimer >= invencibilityTime * 1000) invincible = false;
}

void PlayerAnimationComponent::endAnim()
{
	if (currentAnimation == ATTACK ||currentAnimation == VANISH || currentAnimation == DIE) {
		if (currentAnimation == DIE) ent_->getComponent<Health>()->recall();
		currentAnimation = IDLE;
	}
}