#pragma once
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include "FramedImage.h"

class PlayerAttack;

enum EarthAnims { ADVANCE, BACK };

class earthAnimationController: public Component
{
private:
	anims::Entities eAnims;
	FramedImage* image;
	PlayerAttack* playerAttack;
	int currentAnimation, timer_, startingCol;
	int animationTime;
	const int FRAME_ANIMATION_TIME = 6;
public:
	constexpr static ecs::cmpId_type id = ecs::_EARTH_ATTACK_ANIM;

	earthAnimationController(anims::Entities e) : eAnims(e) 
	{
		timer_ = 0;
		startingCol = 0;
	};
	virtual ~earthAnimationController() {};
	void initComponent();
	virtual void update();
	inline int getState() { return currentAnimation; }
	void setState(int newState, int col = -1);
	void endAnim();
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME;; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
};

