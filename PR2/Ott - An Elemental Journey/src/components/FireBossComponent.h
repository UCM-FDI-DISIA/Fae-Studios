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
	class FramedImage* fImg;

	int specialAttackTimer = 0, timeSpecialAttack = 10000, normalAttackTimer = 0, timeNormalAttack = 3000, stunTimer = 0, timeStunned = 5, waitTimer, maxWait = 6000;
	bool stunned = false;
	bool falling = true, start = false, outRage = false;
	int endY, startX;
	Vector2D pPos;
	void spawnPillars();
	void shootAtPlayer();
	void meleePlayer();
	void startPosition();
public:
	FireBossComponent();
	virtual void initComponent();
	virtual void update();
	void stunBoss();
	inline bool isStunned() { return stunned; }
	inline void activateBoss() { start = true; }
	void resetBoss();
	inline void setAnimComponent(FireBossAnimation* a) { fAnim_ = a; }
	
	constexpr static ecs::cmpId_type id = ecs::_BOSS;
};

