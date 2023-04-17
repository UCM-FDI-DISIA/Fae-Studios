#pragma once
#include "FramedImage.h"
#include "Health.h"

enum GrassAnims { STOPPED, MOVING };

class GrassAnimationComponent : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_LAMP_ANIM;

	GrassAnimationComponent() = default;
	~GrassAnimationComponent() = default;

	inline void startAnim() {
		state = MOVING; timer_ = 0;
		if(playerHealth_->getElement() == ecs::Earth)
			sdlutils().soundEffects().at("grassMoving").playFor(2000, 0, ecs::_channel_AMBIENTAL);
	};
	inline void stopAnim() {
		state = STOPPED;
		col = 0;
		timer_ = 0;
	};

	inline virtual void initComponent() {
		image_ = ent_->getComponent<FramedImage>();
		playerHealth_ = mngr_->getPlayer()->getComponent<Health>();
		assert(image_ != nullptr);
	}
	void update() {
		if (playerHealth_->getElement() == ecs::Earth && state == MOVING) {
			timer_++;
			if (timer_ > (getTPerFrame(state) * getNFrames(state)) + 1) {
				timer_ = 0;
				col = 0;
			}
			if (col != getNFrames(state) + getColNum(state) - 1) 
				col = (timer_ / getTPerFrame(state)) % getNFrames(state) + getColNum(state);
		}
		else col = 0;
		image_->setCol(col);
	}
private:
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }

	anims::Entities eAnims = anims::GRASS_ANIM;
	bool forward = true;
	FramedImage* image_;
	int timer_ = 0;
	const int FRAME_ANIMATION_TIME = 5;
	int col = 0;
	GrassAnims state = STOPPED;
	Health* playerHealth_;
};
