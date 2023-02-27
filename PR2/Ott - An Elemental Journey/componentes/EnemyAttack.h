#pragma once
#include "Component.h"
class EnemyAttack : public Component
{
public:
	EnemyAttack() : Component() { state = normal; };
	enum attackState {normal, preparing, attacking, afterAttack, laying };
	inline attackState getState() { return state; }
	inline void setState(attackState s) { state = s; }
private:
	attackState state;
};

