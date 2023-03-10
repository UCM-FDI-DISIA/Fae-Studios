#pragma once
#include "Health.h"
#include "EnemyAttack.h"
#include "EnemyAnimationController.h"
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
	void Attack();
private:
	Entity* player;
	Health* playerHealth;
	Health* health;
	EnemyAnimationComponent* eAnims_;

	EnemyAttack* enemyAttack;

};

