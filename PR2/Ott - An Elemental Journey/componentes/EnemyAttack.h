#pragma once
#include "Transform.h"
#include "PhysicsComponent.h"
#include<SDL.h>

class Health;
class EnemyShootingAttack;
class EnemyMeleeAttack;
class EnemyAnimationComponent;

class EnemyAttack : public Component
{
	/*uint PREPARING_TIME = 1000;
	uint ATTACKING_TIME = 1000;
	uint DAMAGED_TIME = 1000;
	uint LAYING_TIME = 3000;*/
public:
	constexpr static cmpId_type id = ecs::_TRIGGER;
	EnemyAttack(int time, int w = 50 , int h = 50) : Component() {
		state = normal;
		transform = nullptr;
		physics = nullptr;
		player = nullptr;
		trigger.x = 0; trigger.y = 0;
		trigger.w = w; trigger.h = h;

		TIME_BETWEEN_ATTACKS = time;


		startAttackingTime = SDL_GetTicks();
	}
	enum attackState {normal, preparing, attacking, afterAttack, laying };
	inline attackState getState() { return state; }
	inline void setState(attackState s) { state = s; }
	inline int getTimeBetweenAttacks() { return TIME_BETWEEN_ATTACKS; }
	void initComponent() override;
	void update() override;
	bool requestAttack();
	void Attack();
	void SetRefs(EnemyAnimationComponent* a, EnemyShootingAttack* s = nullptr, EnemyMeleeAttack* m = nullptr);
private:
	bool hasAttacked;
	attackState state;
	SDL_Rect trigger;
	Transform* transform;
	PhysicsComponent* physics;
	EnemyShootingAttack* shootingAttack_;
	EnemyMeleeAttack* meleeAttack_;
	EnemyAnimationComponent* eAnim_;
	Entity* player;
	Health* health_;

	uint TIME_BETWEEN_ATTACKS;

	int startAttackingTime = 0;

	void MoveTriggers();
};

