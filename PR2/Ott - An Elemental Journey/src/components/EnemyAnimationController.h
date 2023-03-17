#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../ecs/anims.h"
#include <SDL.h>
#include "EnemyMovement.h"
#include "FramedImage.h"
// LIMPIO

enum EnemyAnims { IDLE_ENEMY, DIE_ENEMY, ATTACK_ENEMY, PREPARE_ATTACK_ENEMY, WALK_ENEMY, AFTER_ATTACK_ENEMY };

class Health;
class FramedImage;

class EnemyAnimationComponent : public Component {
public:
	constexpr static ecs::cmpId_type id = ecs::_ENEMYANIM;

	EnemyAnimationComponent(anims::Entities e) : eAnims(e) {};
	virtual ~EnemyAnimationComponent();
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
	int currentAnimation = IDLE_ENEMY;
	anims::Entities eAnims;
	FramedImage* image;
	Health* health_;
	EnemyMovement* eMovement_;
	EnemyAttack* eAttack_;

	int posInList, roomNum;

	int damageTimer_, damageStartTime_, timer_ = 0;
	const int maxDamagedTimer_ = 500, FRAME_ANIMATION_TIME = 6;
};
