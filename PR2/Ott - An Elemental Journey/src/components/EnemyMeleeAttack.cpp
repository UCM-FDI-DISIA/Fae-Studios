#include "EnemyMeleeAttack.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"

void EnemyMeleeAttack::initComponent() {
	player = mngr_->getPlayer();
	playerHealth = player->getComponent<Health>();
	health = ent_->getComponent<Health>();
	enemyAttack = ent_->getComponent<EnemyAttack>();
}

void EnemyMeleeAttack::update() {
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0) {
		playerHealth->recieveDamage(health->getElement());
		//Aplicar knockback
	}
}
