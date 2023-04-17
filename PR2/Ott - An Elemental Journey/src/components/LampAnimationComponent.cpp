#include "LampAnimationComponent.h"

void LampAnimationComponent::update(){
	if (playerHealth_->getElement() == ecs::Light || state == CHANGING) {
		if (state == CHANGING) {
			if (forward) {
				timer_++;
				if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1) {
					timer_ = 0;
					state = ON;
					col = 4;
				}
				if (col != getNFrames(state) + getColNum(state) - 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
			}
			else {
				timer_--;
				if (timer_ < 0) {
					timer_ = 0;
					state = OFF;
					col = 0;
				}
				if (col != 1) col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
			}
		}
		else if (state == OFF && nearPlayer) { startOnwardsAnim(); }
	}
	else if (state != OFF) startBackwardsAnim();
	image_->setCol(col);
}