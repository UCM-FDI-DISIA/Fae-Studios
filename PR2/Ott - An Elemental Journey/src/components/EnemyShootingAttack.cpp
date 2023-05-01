#include "EnemyShootingAttack.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Bullet.h"
#include "../sdlutils/SDLUtils.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

void EnemyShootingAttack::initComponent()
{
	player = mngr_->getPlayer();
	playerHealth = player->getComponent<Health>();
	health = ent_->getComponent<Health>();
	enemyAttack = ent_->getComponent<EnemyAttack>();
}

void EnemyShootingAttack::Attack() {
	if (enemyAttack->requestAttack() && playerHealth->getHealth() > 0) {
		auto bullet = mngr_->addEntity(ecs::_grp_PROYECTILES);
		auto pc = bullet->addComponent<PhysicsComponent>();
		if (ent_->getComponent<PhysicsComponent>()->getLookDirection())
			bullet->addComponent<Transform>(ent_->getComponent<Transform>()->getPosition().getX() + ent_->getComponent<Transform>()->getWidth() / 3, ent_->getComponent<Transform>()->getPosition().getY() + ent_->getComponent<Transform>()->getHeight() / 2, 30, 30);
		else
			bullet->addComponent<Transform>(ent_->getComponent<Transform>()->getPosition().getX(), ent_->getComponent<Transform>()->getPosition().getY() + ent_->getComponent<Transform>()->getHeight() / 2, 30, 30);
		if (player->getComponent<Transform>()->getPosition().getX() > ent_->getComponent<Transform>()->getPosition().getX())
			pc->setVelocity(Vector2D(3, 0));
		else
			pc->setVelocity(Vector2D(-3, 0));
		pc->setGravity(false);
		bullet->addComponent<Image>(&sdlutils().images().at("spores")); 
		bullet->addComponent<Bullet>(health->getElement(), ent_);
		attackingTime = SDL_GetTicks();
	}
}
