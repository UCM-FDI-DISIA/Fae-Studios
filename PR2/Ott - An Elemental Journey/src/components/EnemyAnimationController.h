#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include "FramedImage.h"

enum EnemyAnims { IDLE_ENEMY, DIE_ENEMY, ATTACK_ENEMY, PREPARE_ATTACK_ENEMY, WALK_ENEMY };

class EnemyAnimationComponent : public Component {
private:
	const int maxDamagedTimer_ = 500, FRAME_ANIMATION_TIME = 6;
	
	bool damaged;
	int currentAnimation;
	anims::Entities eAnims;
	FramedImage* image;

	int damageTimer_, damageStartTime_, timer_;

public:
	constexpr static ecs::cmpId_type id = ecs::_ANIM;

	EnemyAnimationComponent(anims::Entities e) : eAnims(e), damaged(false), currentAnimation(IDLE_ENEMY)
		, image(nullptr), damageTimer_(0), damageStartTime_(0), timer_(0) {};
	virtual ~EnemyAnimationComponent() = default;
	
	void initComponent();
	void endAnim();
	virtual void update();

	inline int getState() { return currentAnimation; }
	inline void setState(int newState) { currentAnimation = newState; timer_ = 0; }
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME;; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
	inline bool isDamaged() { return damaged; }
	inline void damage() { damaged = true; }
};
