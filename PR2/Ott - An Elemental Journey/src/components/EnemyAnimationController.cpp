#include "EnemyAnimationController.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"
#include "PlayerAnimationComponent.h"

// LIMPIO

void EnemyAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImage>();
}

void EnemyAnimationComponent::update() {

	int state = currentAnimation;
	timer_++;

	if (damaged) {
		image->setRow(1);
		damageTimer_ = SDL_GetTicks() - damageStartTime_;
		if (damageTimer_ >= maxDamagedTimer_) {
			damaged = false;
		}
	}
	else { damageStartTime_ = SDL_GetTicks(); image->setRow(0); }

	int col = image->getCurrentCol();

	if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

	image->setCol(col);

	if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
	{
		endAnim();
	}

	/*
	if (currentAnimation == ATTACK_ENEMY || currentAnimation == DIE_ENEMY) return;
	Vector2D vel = ent_->getComponent<PhysicsComponent>()->getVelocity();
	if (vel.getX() != 0) currentAnimation = WALK_ENEMY;
	else currentAnimation = IDLE_ENEMY;*/
}

void EnemyAnimationComponent::endAnim() {
	if (currentAnimation == PREPARE_ATTACK_ENEMY)
	{
		setState(ATTACK_ENEMY);
		// el enemigo ataca, aquí debería llamarse a una función de ataque
	}
	else { setState(IDLE); }
	timer_ = 0;
}