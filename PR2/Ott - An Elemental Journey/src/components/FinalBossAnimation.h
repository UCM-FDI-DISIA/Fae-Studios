#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include "FramedImage.h"
// LIMPIO

enum FinalBossAnims {IDLE_BOSS, IDLE_BOSS2, HEALTH_BOSS, STUN_BOSS, DIE_BOSS };

class Health;
class FramedImage;

class FinalBossAnimation : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_FINAL_BOSS_ANIMATION;

	FinalBossAnimation(anims::Entities e) : eAnims(e) {};
	virtual ~FinalBossAnimation();
	void initComponent();
	virtual void update();
	inline int getState() { return currentAnimation; }
	void setState(int newState);
	void endAnim();
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME;; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
	inline bool isDamaged() { return damaged; }
	inline void damage() { damaged = true; }
	inline void setPosInList(int pos, int room) { posInList = pos; roomNum = room; }

private:
	bool damaged = false;
	int currentAnimation = IDLE_BOSS;
	anims::Entities eAnims;
	FramedImage* image;
	//Health* health_;
	

	Entity* map;//fa falta per recarga de cambres?
	int posInList, roomNum;

	int timer_ = 0;
	int moveTimer_ = 0,MOVE_TIME;
	const int  FRAME_ANIMATION_TIME = 6;
	int col, row, frames;

};
