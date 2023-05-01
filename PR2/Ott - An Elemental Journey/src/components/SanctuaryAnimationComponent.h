#include "../ecs/Component.h"
#include "FramedImage.h"
#pragma once
enum Sanctuary_States { SANCT_OFF, SANCT_STARTING, SANCT_ON, SANCT_ACTIVE };
class SanctuaryAnimationComponent : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_SANCTUARY_ANIM;

	SanctuaryAnimationComponent() = default;
	~SanctuaryAnimationComponent() = default;
	inline void initComponent() override {
		image_ = ent_->getComponent<FramedImage>();
		sdlutils().soundEffects().at("sanctuaryStart").setVolume(50);
		sdlutils().soundEffects().at("sanctuaryStop").setVolume(50);
		sdlutils().soundEffects().at("sanctuaryRest").setVolume(50);
		assert(image_ != nullptr);
	}

	void update() override {
		if (state_ == SANCT_ON || state_ == SANCT_OFF) {
			col = getColNum(state_);
			timer_ = 0;
		}
		else {
			if (!backwards) {
				timer_++;
				if (col != getNFrames(state_) + getColNum(state_) - 1) col = (timer_ / getTPerFrame(state_)) % getNFrames(state_) + getColNum(state_);
				if (timer_ > (getTPerFrame(state_) * getNFrames(state_)) + 1) {
					if (state_ == SANCT_STARTING)
						state_ = SANCT_ON;
					else
						timer_ = 0;
					col = getColNum(state_);
				}
			}
			else {
				timer_--;
				if (col != 1) col = (timer_ / getTPerFrame(state_)) % getNFrames(state_) + getColNum(state_);
				if (timer_ <= 0) {
					state_ = SANCT_OFF;
					backwards = false;
				}
			}
		}
		image_->setCol(col);
	}

	inline void activate() { 
		state_ = SANCT_ACTIVE; 
		sdlutils().soundEffects().at("sanctuaryRest").play(0, ecs::_channel_AMBIENTAL);
	};
	inline void deactivate() { state_ = SANCT_OFF; }
	inline void start() { 
		if (state_ != SANCT_ACTIVE) {
			state_ = SANCT_STARTING; 
			sdlutils().soundEffects().at("sanctuaryStart").play(0, ecs::_channel_AMBIENTAL);
		}
	}
	inline void stop() {
		if (state_ != SANCT_ACTIVE)
		{
			backwards = true; state_ = SANCT_STARTING; timer_ = (getTPerFrame(state_) * getNFrames(state_)) - 1;
			sdlutils().soundEffects().at("sanctuaryStop").play(0, ecs::_channel_AMBIENTAL);
		}
	}
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
	anims::Entities eAnims = anims::SANCTUARY_ANIM;
	const int FRAME_ANIMATION_TIME = 5;

	bool backwards = false;
	int timer_ = 0;
	Sanctuary_States state_ = SANCT_OFF;
	FramedImage* image_;
	int col = 0;
};

