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
	//SDL_Rect collider;
	int specialAttackTimer = 0, timeSpecialAttack = 12, normalAttackTimer = 0, timeNormalAttack = 4, ambushSpeed = 1, speed=0, rSpeed=1,stunTimer = 0, timeStunned = 5;
	bool ambushing = false, retirada = false, stunned = false;
	void startSpecialAttack();
	void startNormalAttack();
	void spawnPillars();
	void shootAtPlayer();
public:
	FireBossComponent();
	virtual void initComponent();
	virtual void update();
	void ambush();
	void stunBoss();
	void combo();
	inline bool isMoving() { return ambushing || retirada; }
	inline void setAnimComponent(FireBossAnimation* a) { fAnim_ = a; }
	constexpr static ecs::cmpId_type id = ecs::_BOSS;
};

