#include "EnemyMeleeAttack.h"
#include "../Src/Entity.h"

void EnemyMeleeAttack::initComponent()
{
	playerHealth = player->getComponent<Health>();
	health = ent_->getComponent<Health>();
	enemyAttack = ent_->getComponent<EnemyAttack>();
}

void EnemyMeleeAttack::update()
{
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0) {
		playerHealth->recieveDamage(health->getElement());
		//Aplicar knockback
	}
		
}
