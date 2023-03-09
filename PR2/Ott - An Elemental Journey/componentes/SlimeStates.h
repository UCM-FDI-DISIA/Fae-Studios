#pragma once
#include "EnemyAttack.h"
#include "Health.h"
class SlimeStates : public Component
{
private:
	bool ajusta;
	Entity* player;
	EnemyAttack* attack;
	PhysicsComponent* physics;
	Transform* transform;
	/*Health* health;
	Health* playerHealth;
	float attackingTime;*/
	SDL_Rect damageZone;
	void layDownAdjust();
	void getUpAdjust();
	// pa luego cuando tenga viditas uwu
	// void divide();
public:
	constexpr static cmpId_type id = ecs::_ENEMYSTATES;
	SlimeStates() : Component() {
		ajusta = true;
		player = nullptr;
		attack = nullptr;
		damageZone = { 0, 0, 0, 0 };
		physics = nullptr;
		transform = nullptr;
		/*health = nullptr;
		playerHealth = nullptr;
		attackingTime = SDL_GetTicks();*/
	}
	void initComponent() override;
	void update() override;
};

