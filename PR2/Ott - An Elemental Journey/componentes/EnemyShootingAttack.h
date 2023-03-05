#pragma once
#include "EnemyAttack.h"
#include "Health.h"
class EnemyShootingAttack : public Component
{
	const int SHOOTING_TIME = 1000;
public:
	constexpr static cmpId_type id = ecs::_ATTACK;
	EnemyShootingAttack() : Component() {
		player = nullptr;
		health = nullptr;
		playerHealth = nullptr;
		enemyAttack = nullptr;
		attackingTime = SDL_GetTicks();
	}
	void initComponent() override;
	void update() override;
private:
	Entity* player;
	Health* health;
	Health* playerHealth;
	EnemyAttack* enemyAttack;

	int attackingTime = 0;
};
