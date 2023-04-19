#pragma once
#include "../ecs/Component.h"
#include <array>
#include "../ecs/anims.h"
#include <SDL.h>
#include "Transform.h"
#include "FramedImage.h"

class GeneralAnimationController : public Component
{

public:
	constexpr static ecs::cmpId_type id = ecs::_ANIM;
	GeneralAnimationController(anims::Entities e, Entity* e1);
	virtual ~GeneralAnimationController(){};
	virtual void update();
	
	
	inline int getTPerFrame() { return anims::animations[eAnims][0].tPerFrame / FRAME_ANIMATION_TIME; }
	inline int getNFrames() { return anims::animations[eAnims][0].numFrames; }
	inline int getRowNum() { return anims::animations[eAnims][0].rowNum; }
	inline int getColNum() { return anims::animations[eAnims][0].colNum; }

private:

	const int FRAME_ANIMATION_TIME = 5;
	int startAnimTicks;
	anims::Entities eAnims;
	FramedImage* image;
	int timer_ = 0;
	
};

