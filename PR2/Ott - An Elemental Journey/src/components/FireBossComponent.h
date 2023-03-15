#pragma once
#include "../ecs/Component.h"

class FireBossComponent:public Component
{ 
private:
	class Transform* tr_;
	int specialAttackTimer = 0, timeSpecialAttack = 15, normalAttackTimer = 0, timeNormalAttack = 4;
public:
	FireBossComponent();
	virtual void initComponent();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_BOSS;
};

