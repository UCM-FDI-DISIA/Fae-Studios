#pragma once
#include "Component.h"
#include <array>
#include <SDL.h>
enum Animations { IDLE, WALK, RUN, JUMP_UP, PEAK, FALL, LAND, VANISH, DIE, ATTACK };

class PlayerAnimationComponent : public Component
{
public:
	PlayerAnimationComponent();
	virtual ~PlayerAnimationComponent();
	virtual void update();
	inline int getState() { return currentAnimation; }
	inline void setState(int newState) { currentAnimation = newState; startAnimTicks = SDL_GetTicks(); }
	void endAnim();
	inline int getTPerFrame(int i) { return animArray[i].tPerFrame; }
	inline int getNFrames(int i) { return animArray[i].numFrames; }
	inline int getRowNum(int i) { return animArray[i].rowNum; }
	inline void playerDamaged() { invincible = true; damageTimer = SDL_GetTicks(); }
	inline bool isInvincible() { return invincible; }
	inline int getStartTicks() { return startAnimTicks; }
	constexpr static cmpId_type id = ecs::_ANIM;
private:
	bool invincible = false;
	int damageTimer, invencibilityTime = 3;
	int currentAnimation = IDLE;
	int startAnimTicks;
	struct animDescription
	{
		int tPerFrame;
		int numFrames;
		int rowNum;
	};
	animDescription animArray[10] = { {300,2,0}, {200,4,2}, {100,8,3}, {100,4,5}, {100,1,5}, {100,1,5}, {100,2,5}, {150,4,6}, {200,8,7}, {100,8,8} };
};