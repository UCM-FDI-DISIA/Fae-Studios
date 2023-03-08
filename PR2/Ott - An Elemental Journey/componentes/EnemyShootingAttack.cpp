#include "EnemyShootingAttack.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"
#include "Bullet.h"
void EnemyShootingAttack::initComponent()
{
	player = mngr_->getPlayer();
	playerHealth = player->getComponent<Health>();
	health = ent_->getComponent<Health>();
	enemyAttack = ent_->getComponent<EnemyAttack>();
}

void EnemyShootingAttack::update() //Completar con constructoras y nuevos m�todos de las balas (a lo mejor manager deber�a tener un m�todo de crear balas)
{
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0 && SDL_GetTicks() - attackingTime >= SHOOTING_TIME) {
		auto bullet = mngr_->addEntity(ecs::_grp_PROYECTILES);
		if(ent_->getComponent<PhysicsComponent>()->getLookDirection())
			bullet->addComponent<Transform>(ent_->getComponent<Transform>()->getPos().getX() + ent_->getComponent<Transform>()->getW() / 3, ent_->getComponent<Transform>()->getPos().getY() + ent_->getComponent<Transform>()->getH() / 2, 2, 2);
		else
			bullet->addComponent<Transform>(ent_->getComponent<Transform>()->getPos().getX(), ent_->getComponent<Transform>()->getPos().getY() + ent_->getComponent<Transform>()->getH() / 2, 2, 2);
		bullet->addComponent<PhysicsComponent>();
		bullet->getComponent<PhysicsComponent>()->setGravity(false);
		if (player->getComponent<Transform>()->getPos().getX() > ent_->getComponent<Transform>()->getPos().getX())
			bullet->getComponent<PhysicsComponent>()->getVelocity() = Vector2D(1, 0);
		else
			bullet->getComponent<PhysicsComponent>()->getVelocity() = Vector2D(-1, 0);
		bullet->addComponent<Image>(mngr_->getTexture(5)); //Falta textura
		bullet->addComponent<Bullet>(health->getElement());
		attackingTime = SDL_GetTicks();
	}
}
