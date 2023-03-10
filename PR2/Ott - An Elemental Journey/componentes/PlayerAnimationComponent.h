#pragma once
#include "Component.h"
#include <array>
#include <SDL.h>
#include "../Src/anims.h"
enum Animations { IDLE, WALK, RUN, JUMP_UP, PEAK, FALL, LAND, VANISH, DIE, ATTACK };

class FramedImageOtt;
class Health;

class PlayerAnimationComponent : public Component
{
public:
	constexpr static cmpId_type id = ecs::_ANIM;

	PlayerAnimationComponent(anims::Entities e = anims::OTT_ANIM);
	virtual ~PlayerAnimationComponent();
	virtual void update();
	void initComponent();
	inline int getState() { return state_; }
	void setState(int newState);
	void endAnim();
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }
	inline void playerDamaged() { invincible = true; damageTimer = SDL_GetTicks(); }
	inline bool isInvincible() { return invincible; }
	inline int getStartTicks() { return startAnimTicks; }
	inline void isShielded(bool b) { shielded = b; }
	inline bool getShielded() { return shielded; }
	inline void changeElem(ecs::elements newElem) { elemToChange = newElem; }

private:
	ecs::elements elemToChange;
	bool invincible = false, shielded = false, changingElem = false;
	int damageTimer, invencibilityTime = 2;
	int timer_ = 0;
	const int FRAME_ANIMATION_TIME = 5;
	int state_ = IDLE;
	int startAnimTicks;
	FramedImageOtt* image;
	Health* health;
	anims::Entities eAnims;
};