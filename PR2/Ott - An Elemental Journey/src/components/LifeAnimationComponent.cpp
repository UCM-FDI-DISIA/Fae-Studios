#include "LifeAnimationComponent.h"

void LifeAnimationComponent::update() {
	if (forward) {
		timer_++;
		int col = image_->getCurrentCol();

		if (col != getNFrames() + getColNum() - 1) col = (timer_ / getTPerFrame()) % getNFrames() + getColNum();

		image_->setCol(col);

		if (timer_ > getNFrames() * getTPerFrame() + 1) endAnim();
	}
	else {
		timer_--;
		int col = image_->getCurrentCol();

		if (col != getNFrames() + getColNum() - 1) col = (timer_ / getTPerFrame()) % getNFrames() + getColNum();

		image_->setCol(col);
		if (timer_ <= 0) endAnim();
	}
}

void LifeAnimationComponent::initComponent() {
	image_ = ent_->getComponent<FramedImage>();
}

void LifeAnimationComponent::endAnim() {
	forward = !forward;
}