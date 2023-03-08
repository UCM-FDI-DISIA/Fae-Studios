#include "EnemyAnimationController.h"
#include "../Src/Entity.h"

void EnemyAnimationComponent::update() {
	
	if (damaged) {
		timer_ = SDL_GetTicks() - startTime_;
		if (timer_ >= damagedTimer_) {
			damaged = false;
		}
	}
	else startTime_ = SDL_GetTicks();

	/*
	if (currentAnimation == ATTACK_ENEMY || currentAnimation == DIE_ENEMY) return;
	Vector2D vel = ent_->getComponent<PhysicsComponent>()->getVelocity();
	if (vel.getX() != 0) currentAnimation = WALK_ENEMY;
	else currentAnimation = IDLE_ENEMY;*/
}

void EnemyAnimationComponent::endAnim() {
	if (currentAnimation == ATTACK_ENEMY || currentAnimation == DIE_ENEMY) setState(IDLE);
	else if (currentAnimation == PREPARE_ATTACK_ENEMY) setState(ATTACK_ENEMY);
}