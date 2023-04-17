#pragma once
#include "FramedImage.h"
#include "Health.h"

enum LampAnims { OFF, CHANGING, ON };

class LampAnimationComponent : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_LAMP_ANIM;
	
	LampAnimationComponent() = default;
	~LampAnimationComponent() = default;

	inline void setNear(bool nearPlayer_) { nearPlayer = nearPlayer_; }
	inline void startOnwardsAnim() { 
		shouldAnimate = true; forward = true; 
		state = CHANGING; timer_ = 0; 
		sdlutils().soundEffects().at("lampActivation").playFor(1000, 0, ecs::_channel_AMBIENTAL);
	};
	inline void startBackwardsAnim() {
		shouldAnimate = true; forward = false; 
		state = CHANGING;
		sdlutils().soundEffects().at("lampActivationBackwards").playFor(1000, 0, ecs::_channel_AMBIENTAL);
		timer_ = (getTPerFrame(state) * getNFrames(state)); };

	inline virtual void initComponent() {
		image_ = ent_->getComponent<FramedImage>();
		playerHealth_ = mngr_->getPlayer()->getComponent<Health>();
		assert(image_ != nullptr);
	}
	virtual void update();
private:
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }

	bool nearPlayer = false;
	anims::Entities eAnims = anims::LAMP_ANIM;
	bool shouldAnimate = false;
	bool forward = true;
	FramedImage* image_;
	int timer_ = 0;
	const int FRAME_ANIMATION_TIME = 5;
	int col = 0;
	LampAnims state = OFF;
	Health* playerHealth_;
};
