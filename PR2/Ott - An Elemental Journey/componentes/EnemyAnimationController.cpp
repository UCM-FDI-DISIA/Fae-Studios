#include "EnemyAnimationController.h"
#include "../Src/Entity.h"
#include "FramedImage.h"

void EnemyAnimationComponent::setState(int newState) { 
	if (!health_->isDead() && currentAnimation != DIE_ENEMY) { 
		currentAnimation = newState; 
		startAnimTicks = SDL_GetTicks(); 
		timer_ = 0; 
	} 
}


void EnemyAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImageEnemy>();
	health_ = ent_->getComponent<Health>();
}

void EnemyAnimationComponent::update() {
	int state = currentAnimation;
	cout << currentAnimation << endl;
	timer_ = (timer_ + 1) % (getTPerFrame(state) * getNFrames(state)) +1;

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