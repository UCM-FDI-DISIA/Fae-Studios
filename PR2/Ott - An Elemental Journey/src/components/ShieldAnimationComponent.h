#include "../ecs/Component.h"
#include "FramedImage.h"
#include "../ecs/anims.h"
#pragma once

enum Shield_States { SHIELD_NORMAL, SHIELD_BLOCK, SHIELD_BREAK  };

class ShieldAnimationComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_SHIELD_ANIM;
	ShieldAnimationComponent() = default;
	~ShieldAnimationComponent() = default;

	void blockAttack() {
		state_ = SHIELD_BLOCK;
		timer_ = 0;
	}
	void breakShield() {
		state_ = SHIELD_BREAK;
		timer_ = 0;
	}
	inline void initComponent() override {
		image_ = ent_->getComponent<FramedImageOtt>();
		assert(image_ != nullptr);
	}
	inline void update() override {
		if (state_ == SHIELD_NORMAL) {
			col = 0;
			timer_ = 0;
		}
		else {
			timer_++;
			if (col != getNFrames(state_) + getColNum(state_) - 1) 
				col = (timer_ / getTPerFrame(state_)) % getNFrames(state_) + getColNum(state_);

			if (timer_ > (getTPerFrame(state_) * getNFrames(state_)) + 1)
				state_ = SHIELD_NORMAL;
		}
		image_->setShieldCol(col);
	}

private:
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }

	anims::Entities eAnims = anims::SHIELD_ANIM;
	Shield_States state_;
	const int FRAME_ANIMATION_TIME = 5;
	int timer_ = 0;
	int col = 0;
	FramedImageOtt* image_;
};