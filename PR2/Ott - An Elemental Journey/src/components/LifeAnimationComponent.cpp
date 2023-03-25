#include "LifeAnimationComponent.h"

void LifeAnimationComponent::update() {
	if (forward) {
		timer_++;
		col = image_->getCurrentCol();

		if (col != 9) col = (timer_ / getTPerFrame()) % getNFrames();

		image_->setCol(col);

		if (timer_ > getNFrames() * getTPerFrame() + 1) endAnim();
	}
	else {
		timer_--;
		col = image_->getCurrentCol();

		if (col != 0) col = (timer_ / getTPerFrame()) % getNFrames() + getColNum();

		image_->setCol(col);
		if (timer_ <= 0) endAnim();
	}
}

void LifeAnimationComponent::initComponent() {
	image_ = ent_->getComponent<FramedImage>();
}

void LifeAnimationComponent::endAnim() {
	forward = !forward;
	if (forward) {
		col = 0; timer_ = 0;
	}
	else { col = 9; timer_ = getNFrames() * getTPerFrame() - 1; }
}