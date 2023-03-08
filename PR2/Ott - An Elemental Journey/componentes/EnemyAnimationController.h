#pragma once
#include "../dependencies/Vector2D.h"
#include "Component.h"
#include "../Src/anims.h"
#include <SDL.h>

enum EnemyAnims { IDLE_ENEMY, DIE_ENEMY, ATTACK_ENEMY, WALK_ENEMY };

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
	inline void enemyDamaged() { invincible = true; damageTimer = SDL_GetTicks(); }
	inline bool isInvincible() { return invincible; }
	inline int getStartTicks() { return startAnimTicks; }

private:
	bool invincible = false;
	int damageTimer, invencibilityTime = 3;
	int currentAnimation = IDLE_ENEMY;
	int startAnimTicks;
	anims::Entities eAnims;
};
