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
	int state = currentAnimation;
	timer_++;

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
	timer_ = 0;
	currentAnimation = IDLE_WATERBOSS;
}