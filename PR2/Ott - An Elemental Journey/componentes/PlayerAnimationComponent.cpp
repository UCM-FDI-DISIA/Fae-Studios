#include "PlayerAnimationComponent.h"
#include "PhysicsComponent.h"
#include "../Src/Entity.h"
#pragma once
PlayerAnimationComponent::PlayerAnimationComponent(anims::Entities e)
{
	eAnims = e;
}

void PlayerAnimationComponent::update()
{
	if (currentAnimation == ATTACK || currentAnimation == VANISH || currentAnimation == DIE) return;
	auto physics = ent_->getComponent<PhysicsComponent>();
	Vector2D vel = physics->getVelocity();
	if (vel.getY() == 0) {
		if (vel.getX() != 0) currentAnimation = RUN;
		else currentAnimation = IDLE;
	}
	else if(physics->isClimbing())  currentAnimation = IDLE;
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

PlayerAnimationComponent::~PlayerAnimationComponent()
{
}