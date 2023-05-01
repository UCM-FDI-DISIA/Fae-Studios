#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include "FramedImage.h"
#pragma once

class LifeAnimationComponent : public Component {
private:
	int currentAnimation = anims::LIFE_SHARD;
	void endAnim();
	bool forward = true, active_ = false;
	int timer_ = 0;
	int col = 0;
	FramedImage* image_;
	inline int getTPerFrame() { return anims::animations[currentAnimation][0].tPerFrame; }
	inline int getNFrames() { return anims::animations[currentAnimation][0].numFrames; }
	inline int getRowNum() { return anims::animations[currentAnimation][0].rowNum; }
	inline int getColNum() { return anims::animations[currentAnimation][0].colNum; }
public:
	constexpr static ecs::cmpId_type id = ecs::_LIFESHARDANIM;
	LifeAnimationComponent() {};
	virtual ~LifeAnimationComponent() = default;
	virtual void update();
	virtual void initComponent();
	inline void activate() { active_ = true; timer_ = 0; col = 0; forward = true; }
	inline void deactivate() { active_ = false; timer_ = 0; col = 0; image_->setCol(col); }
};