#include "../utils/checkML.h"
#include "ChargedAttackBar.h"

void ChargedAttackBar::render() {
	SDL_Rect tmp = hImage_->getLastHeartPos();
	tmp.x += 90;
	tmp.w = texture_->getFrameWidth() * 2.25;
	tmp.h = texture_->getFrameHeight() * 2.25;
	texture_->renderFrame(tmp, 0, frame_);
}

void ChargedAttackBar::update() {
	charges_ = 8;
	if (charges_ < 8) {
		count_ = 1;
		frame_ = charges_;
	}
	else {
		if (!anim_) {
			frame_ = charges_ + count_;
			if (SDL_GetTicks() - FRAME_TIME >= ticks_) {
				if (glowing_) count_++;
				else count_--;

				ticks_ = SDL_GetTicks();
			}
		}
		else {
			if (!reset_) {
				frame_ = charges_ + ticksCount_;
				if (SDL_GetTicks() - FRAME_TIME >= ticks_) {
					if (ticksCount_ < 14) ticksCount_++;
					ticks_ = SDL_GetTicks();
				}
			}
			else {
				frame_ = charges_ + ticksCount_;
				if (SDL_GetTicks() - FRAME_TIME >= ticks_) {
					if (ticksCount_ > 5) ticksCount_--;
					else {
						anim_ = false;
						reset_ = false;
					}
					ticks_ = SDL_GetTicks();
				}
			}	
		}
	}


	if (frame_ == 13) glowing_ = false;
	else if (frame_ == 9) glowing_ = true;
}