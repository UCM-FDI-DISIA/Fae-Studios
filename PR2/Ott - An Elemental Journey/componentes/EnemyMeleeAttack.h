#pragma once
#include "Health.h"
#include "EnemyAttack.h"
class EnemyMeleeAttack : public Component
{
public:
	constexpr static cmpId_type id = ecs::_ATTACK;
	EnemyMeleeAttack() : Component() {
		player = nullptr;
		playerHealth = nullptr;
		health = nullptr;
		enemyAttack = nullptr;
	}
	void initComponent() override;
	void update() override;
private:
	Entity* player;
	Health* playerHealth;
	Health* health;
	EnemyAttack* enemyAttack;
};
