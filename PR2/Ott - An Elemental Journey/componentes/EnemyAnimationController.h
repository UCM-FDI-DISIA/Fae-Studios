#pragma once
#include "../dependencies/Vector2D.h"
#include "Component.h"
#include "../Src/anims.h"
#include <SDL.h>

enum EnemyAnims { IDLE_ENEMY, DIE_ENEMY, ATTACK_ENEMY, PREPARE_ATTACK_ENEMY, WALK_ENEMY };

class EnemyAnimationComponent : public Component {
public:
	constexpr static cmpId_type id = ecs::_ANIM;

	EnemyAnimationComponent(anims::Entities e) : eAnims(e) {};
	virtual ~EnemyAnimationComponent() {};
	virtual void update();
	inline int getState() { return currentAnimation; }
	inline void setState(int newState) { currentAnimation = newState; startAnimTicks = SDL_GetTicks(); }
	void endAnim();
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame; }
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

	int timer_, startTime_;
	const int damagedTimer_ = 500;
};
