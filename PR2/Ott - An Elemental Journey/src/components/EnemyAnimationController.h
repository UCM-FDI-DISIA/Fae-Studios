#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include "FramedImage.h"

// LIMPIO

enum EnemyAnims { IDLE_ENEMY, DIE_ENEMY, ATTACK_ENEMY, PREPARE_ATTACK_ENEMY, WALK_ENEMY };

class FramedImageEnemy;

class EnemyAnimationComponent : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_ANIM;

	EnemyAnimationComponent(anims::Entities e) : eAnims(e) {};
	virtual ~EnemyAnimationComponent() {};
	void initComponent();
	virtual void update();
	inline int getState() { return currentAnimation; }
	inline void setState(int newState) { currentAnimation = newState; startAnimTicks = SDL_GetTicks(); timer_ = 0; }
	void endAnim();
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME;; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
	inline int getStartTicks() { return startAnimTicks; }
	inline bool isDamaged() { return damaged; }
	inline void damage() { damaged = true; }

private:
	bool damaged = false;
	int currentAnimation = IDLE_ENEMY;
	int startAnimTicks;
	anims::Entities eAnims;
	FramedImage* image;

	int damageTimer_, damageStartTime_, timer_ = 0;
	const int maxDamagedTimer_ = 500, FRAME_ANIMATION_TIME = 6;
};