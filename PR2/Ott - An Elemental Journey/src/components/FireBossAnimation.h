#pragma once
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include "FireBossComponent.h"
enum FireAnims { IDLE_FIREBOSS,AMBUSH_FIREBOSS,ATTACK_FIREBOSS, DIE_FIREBOSS };

//class Health;
class FramedImage;
class FireBossAnimation : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_FIREBOSS_ANIM;
	FireBossAnimation(anims::Entities e) : eAnims(e) {};
	virtual ~FireBossAnimation() {};
	void initComponent() ;
	virtual void update() ;
	inline int getState() { return currentAnimation; }
	inline int getTPerFrame(int i) { return anims::animations[eAnims][i].tPerFrame / FRAME_ANIMATION_TIME; }
	inline int getNFrames(int i) { return anims::animations[eAnims][i].numFrames; }
	inline int getRowNum(int i) { return anims::animations[eAnims][i].rowNum; }
	inline int getColNum(int i) { return anims::animations[eAnims][i].colNum; }

	void setState(int newState);
private:
	bool damaged = false;
	int currentAnimation = IDLE_FIREBOSS;

	//anims::Entities eAnims = anims::MELEE_ANIM;
	anims::Entities eAnims = anims::FIREBOSS_ANIM;;
	FramedImage* image;
	//Health* health_;
	//EnemyMovement* eMovement_;
	//player attack???? para que dependa de si le han atacado
	FireBossComponent* eFireBossComponent_;

	int timer_ = 0;
	const int  FRAME_ANIMATION_TIME = 6;

};

