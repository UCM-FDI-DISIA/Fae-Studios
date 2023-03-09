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
	// si el player tiene mas de cero vidas y esta dentro del trigger de ataque del enemigo y este no le ha atacado ya en la anterior llamada del update, se ataca al jugador
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0 && !enemyAttack->getHasAttacked()) {
		cout << "bonk!" << endl;
		playerHealth->recieveDamage(health->getElement());
		//Aplicar knockback
	}
		
}
