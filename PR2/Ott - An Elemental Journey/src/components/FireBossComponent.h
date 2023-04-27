#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
class FireBossAnimation;

class FireBossComponent:public Component
{ 
private:
	Transform* tr_;
	Entity* player;
	FireBossAnimation* fAnim_;
	PhysicsComponent* p;
	int comboN = 3;
	int currentCombo=0;
	//SDL_Rect collider;
	int specialAttackTimer = 0, timeSpecialAttack = 7, normalAttackTimer = 0, timeNormalAttack = 3, ambushSpeed = 1, speed=0, rSpeed=1,stunTimer = 0, timeStunned = 5, comboTimer = 0, comboTime = 3;
	bool ambushing = false, retirada = false, stunned = false, combo = false;
	void startSpecialAttack();
	void startNormalAttack();
	void spawnPillars();
	void shootAtPlayer();
public:
	FireBossComponent();
	virtual void initComponent();
	virtual void update();
	void ambush();
	inline int getCurrentCombo() { return currentCombo; }
	inline void minusCombo() { currentCombo--; }
	void stunBoss();
	inline bool isMoving() { return ambushing || retirada; }
	inline void setAnimComponent(FireBossAnimation* a) { fAnim_ = a; }
	constexpr static ecs::cmpId_type id = ecs::_BOSS;
};

