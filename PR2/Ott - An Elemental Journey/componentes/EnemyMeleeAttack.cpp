#include "EnemyMeleeAttack.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"

void EnemyMeleeAttack::initComponent()
{
	player = mngr_->getPlayer();
	playerHealth = player->getComponent<Health>();
	health = ent_->getComponent<Health>();
	enemyAttack = ent_->getComponent<EnemyAttack>();
}

void EnemyMeleeAttack::update()
{
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0 && !enemyAttack->getHasAttacked()) {
		cout << "bonk!" << endl;
		playerHealth->recieveDamage(health->getElement());
		//Aplicar knockback
	}
		
}
