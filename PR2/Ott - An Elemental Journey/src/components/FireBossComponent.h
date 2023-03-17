#pragma once
#include "../ecs/Component.h"

class FireBossComponent:public Component
{ 
private:
	class Transform* tr_;
	Entity* player;
	int specialAttackTimer = 0, timeSpecialAttack = 15, normalAttackTimer = 0, timeNormalAttack = 4, ambushSpeed = 1, stunTimer = 0, timeStunned = 5;
	bool ambushing = false, retirada = false, stunned = false;
	void startSpecialAttack();
	void spawnPillars();
	void shootAtPlayer();
public:
	FireBossComponent();
	virtual void initComponent();
	virtual void update();
	void ambush();
	void stunBoss();
	constexpr static ecs::cmpId_type id = ecs::_BOSS;
};

