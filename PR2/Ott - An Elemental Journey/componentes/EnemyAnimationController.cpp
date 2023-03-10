#include "EnemyAnimationController.h"
#include "../Src/Entity.h"
#include "FramedImage.h"

void EnemyAnimationComponent::setState(int newState) { 
	if (!health_->isDead() && currentAnimation != DIE_ENEMY) { 
		currentAnimation = newState; 
		timer_ = 0; 
		image->setCol(getColNum(currentAnimation));
	} 
}


void EnemyAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImageEnemy>();
	health_ = ent_->getComponent<Health>();
	eMovement_ = ent_->getComponent<EnemyMovement>();
	setState(IDLE_ENEMY);
}

void EnemyAnimationComponent::update() {
	if (currentAnimation == IDLE_ENEMY && eMovement_ != nullptr && eMovement_->isMoving()) setState(WALK_ENEMY);
	else if (currentAnimation == WALK_ENEMY && !eMovement_->isMoving()) setState(IDLE_ENEMY);


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

	int col = image->getCurCol();

	if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

	image->setCol(col);

	if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
	{
		endAnim();
	}
	cout << col << endl;

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
	else if (currentAnimation != DIE_ENEMY && eMovement_ != nullptr &&  eMovement_->isMoving()) { setState(WALK_ENEMY); }
	else if (currentAnimation != DIE_ENEMY || currentAnimation == ATTACK) setState(IDLE_ENEMY);
	else ent_->setAlive(false);
	timer_ = 0;
}