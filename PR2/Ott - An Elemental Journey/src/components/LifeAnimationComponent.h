#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include "FramedImage.h"

class LifeAnimationComponent : public Component {
private:
	int currentAnimation = anims::LIFE_SHARD;
	void endAnim();
	bool forward = true;
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
};