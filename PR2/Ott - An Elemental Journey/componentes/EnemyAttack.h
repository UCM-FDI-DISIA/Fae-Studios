#pragma once
#include "Transform.h"
#include "PhysicsComponent.h"
#include<SDL.h>

class Health;

class EnemyAttack : public Component
{
	/*uint PREPARING_TIME = 1000;
	uint ATTACKING_TIME = 1000;
	uint DAMAGED_TIME = 1000;
	uint LAYING_TIME = 3000;*/
public:
	constexpr static cmpId_type id = ecs::_TRIGGER;
	EnemyAttack(int time1, int time2, int time3, int time4, int w = 50 , int h = 50) : Component() {
		state = normal;
		transform = nullptr;
		physics = nullptr;
		player = nullptr;
		trigger.x = 0; trigger.y = 0;
		trigger.w = w; trigger.h = h;

		PHASE1_TIME = time1;
		PHASE2_TIME = time2;
		PHASE3_TIME = time3;
		PHASE4_TIME = time4;
		hasAttacked = false;

		startAttackingTime = SDL_GetTicks();
	}
	enum attackState {normal, preparing, attacking, afterAttack, laying };
	inline attackState getState() { return state; }
	inline void setState(attackState s) { state = s; }
	bool getHasAttacked() { return hasAttacked; }
	void initComponent() override;
	void update() override;
	bool requestAttack();
private:
	bool hasAttacked;
	attackState state;
	SDL_Rect trigger;
	Transform* transform;
	PhysicsComponent* physics;
	Entity* player;
	Health* health_;

	uint PHASE1_TIME;
	uint PHASE2_TIME;
	uint PHASE3_TIME;
	uint PHASE4_TIME;

	int startAttackingTime = 0;

	void MoveTriggers();
};

