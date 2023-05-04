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
}


void WaterBossAnimationComponent::initComponent() {
	image = ent_->getComponent<FramedImage>();
	health_ = ent_->getComponent<Health>();
	setState(IDLE_WATERBOSS);
}

void WaterBossAnimationComponent::update() {
	int state = IDLE_WATERBOSS;
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
	timer_ = 0;
	currentAnimation = IDLE_WATERBOSS;
}