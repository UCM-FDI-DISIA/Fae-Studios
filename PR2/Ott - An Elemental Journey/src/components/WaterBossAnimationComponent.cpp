#include "WaterBossAnimationComponent.h"
#include "../ecs/Entity.h"
#include "FramedImage.h"
#include "PlayerAnimationComponent.h"
#include "../utils/checkML.h"
#include "Health.h"
#include "Generations.h"
#include "FramedImage.h"

// LIMPIO

void WaterBossAnimationComponent::setState(int newState) {
	if (!health_->isDead() && currentAnimation != DIE_WATERBOSS) {
		currentAnimation = newState;
		timer_ = 0;
		image->setCol(getColNum(currentAnimation));
	}
}


void WaterBossAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImage>();
	health_ = ent_->getComponent<Health>();
	setState(IDLE_WATERBOSS);
}

void WaterBossAnimationComponent::update() {
	/*if (currentAnimation == IDLE_WATERBOSS && eMovement_ != nullptr && eMovement_->isMoving()) setState(WALK_WATERBOSS);
	else if (currentAnimation == WALK_WATERBOSS && !eMovement_->isMoving()) setState(IDLE_WATERBOSS);*/


	int state = currentAnimation;
	timer_++;

	//if (damaged) {
	//	image->setRow(1);
	//	damageTimer_ = SDL_GetTicks() - damageStartTime_;
	//	if (damageTimer_ >= maxDamagedTimer_) {
	//		damaged = false;
	//	}
	//}
	//else { damageStartTime_ = SDL_GetTicks(); image->setRow(0); }

	int col = image->getCurrentCol();

	if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);

	image->setCol(col);

	if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1)
	{
		endAnim();
	}
}

void WaterBossAnimationComponent::endAnim() {
	if (currentAnimation == PREPARE_ATTACK_WATERBOSS)
	{
	}
	else if (currentAnimation == ATTACK_WATERBOSS && ent_->hasComponent<Generations>()) setState(AFTER_ATTACK_WATERBOSS);
	else if (currentAnimation != DIE_WATERBOSS || currentAnimation == ATTACK) setState(IDLE_WATERBOSS);
	else ent_->setAlive(false);
	timer_ = 0;
}