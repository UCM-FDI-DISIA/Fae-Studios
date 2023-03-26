#include "EnemyMeleeAttack.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

void EnemyMeleeAttack::initComponent()
{
	player = mngr_->getPlayer();
	playerHealth = player->getComponent<Health>();
	health = ent_->getComponent<Health>();
	enemyAttack = ent_->getComponent<EnemyAttack>();
	eAnims_ = ent_->getComponent<EnemyAnimationComponent>();
}

void EnemyMeleeAttack::Attack() {
	// si el player tiene mas de cero vidas y esta dentro del trigger de ataque del enemigo, se ataca al jugador
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0) {
		playerHealth->recieveDamage(health->getElement(), ent_->getComponent<PhysicsComponent>()->getLookDirection());
		//Aplicar knockback
	}
}

