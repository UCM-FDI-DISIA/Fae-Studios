#pragma once
#include "Component.h"
#include <array>
#include <SDL.h>
#include "../Src/anims.h"
enum Animations { IDLE, WALK, RUN, JUMP_UP, PEAK, FALL, LAND, VANISH, DIE, ATTACK };

class PlayerAnimationComponent : public Component
{
public:
	constexpr static cmpId_type id = ecs::_ANIM;

	PlayerAnimationComponent(anims::Entities e);
	virtual ~PlayerAnimationComponent();
	virtual void update();
	inline int getState() { return currentAnimation; }
	inline void setState(int newState) { currentAnimation = newState; startAnimTicks = SDL_GetTicks(); }
	void endAnim();
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
	inline void playerDamaged() { invincible = true; damageTimer = SDL_GetTicks(); }
	inline bool isInvincible() { return invincible; }
	inline int getStartTicks() { return startAnimTicks; }

private:
	bool invincible = false;
	int damageTimer, invencibilityTime = 3;
	int currentAnimation = IDLE;
	int startAnimTicks;
	anims::Entities eAnims;
};