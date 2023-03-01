#include "EnemyShootingAttack.h"
#include "../Src/Entity.h"
void EnemyShootingAttack::initComponent()
{
	playerHealth = player->getComponent<Health>();
	health = ent_->getComponent<Health>();
	enemyAttack = ent_->getComponent<EnemyAttack>();
}

void EnemyShootingAttack::update() //Completar con constructoras y nuevos m�todos de las balas (a lo mejor manager deber�a tener un m�todo de crear balas)
{
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0 && SDL_GetTicks() - attackingTime >= SHOOTING_TIME) {
		auto bullet = mngr_->addEntity(ecs::_grp_PROYECTILES);
		bullet->addComponent<Transform>();
		bullet->addComponent<PhysicsComponent>();


		attackingTime = SDL_GetTicks();
	}
}
