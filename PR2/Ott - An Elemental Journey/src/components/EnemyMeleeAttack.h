//LIMPIO

#pragma once
#include "Health.h"
#include "EnemyAttack.h"

class EnemyMeleeAttack : public Component {
private:
	Entity* player;
	Health* playerHealth;
	Health* health;
	EnemyAttack* enemyAttack;

public:
	constexpr static ecs::cmpId_type id = ecs::_ATTACK;
	
	EnemyMeleeAttack() : Component() {
		player = nullptr;
		playerHealth = nullptr;
		health = nullptr;
		enemyAttack = nullptr;
	}
	
	void initComponent() override;
	void update() override;
};

