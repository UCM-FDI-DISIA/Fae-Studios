//LIMPIO

#pragma once
#include "Transform.h"
#include "PhysicsComponent.h"

using uint = unsigned int;

enum attackState { normal, preparing, attacking, afterAttack, laying };

class EnemyAttack : public Component {
private:
	attackState state;
	SDL_Rect trigger;
	Transform* transform;
	PhysicsComponent* physics;
	Entity* player;

	int startAttackingTime = 0;
	
	uint PREPARING_TIME = 1000;
	uint ATTACKING_TIME = 1000;
	uint DAMAGED_TIME = 1000;
	uint LAYING_TIME = 3000;

	void MoveTriggers();

public:
	constexpr static ecs::cmpId_type id = ecs::_TRIGGER;
	EnemyAttack(int w = 50 , int h = 50) : Component() {
		state = normal;
		transform = nullptr;
		physics = nullptr;
		player = nullptr;
		trigger.x = 0; trigger.y = 0;
		trigger.w = w; trigger.h = h;

		startAttackingTime = SDL_GetTicks();
	}

	inline attackState getState() { return state; }
	inline void setState(attackState s) { state = s; }
	void initComponent() override;
	void update() override;
	bool requestAttack();
};

