#include "EnemyAnimationController.h"
#include "../Src/Entity.h"
#include "FramedImage.h"

void EnemyAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImageEnemy>();
}

void EnemyAnimationComponent::update() {
	
	int state = currentAnimation;
	timer_ = (timer_ + 1) % (getTPerFrame(state) * getNFrames(state)) +1;
	cout << timer_ << endl;

	if (damaged) {
		image->setRow(1);
		damageTimer_ = SDL_GetTicks() - damageStartTime_;
		if (damageTimer_ >= maxDamagedTimer_) {
			damaged = false;
		}
	}
	else { damageStartTime_ = SDL_GetTicks(); image->setRow(0); }

	int col = image->getCurCol();
	if (col == (getNFrames(state) - 1 + getColNum(state)) &&
		((SDL_GetTicks() - getStartTicks()) / getTPerFrame(state)) % getNFrames(state) == 0)
	{
		endAnim();
	}

	if (state == ATTACK_ENEMY || state == DIE_ENEMY || state == PREPARE_ATTACK_ENEMY) {
		col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
	}
	else {
		col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
	}

	image->setCol(col);

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
	else if (currentAnimation != DIE_ENEMY) { setState(IDLE_ENEMY); }
	else ent_->setAlive(false);
}