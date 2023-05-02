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
		auto tr_ = ent_->getComponent<Transform>();
		if (ent_->getComponent<PhysicsComponent>()->getLookDirection())
			bullet->addComponent<Transform>(tr_->getPosition().getX() + tr_->getWidth() / 3, 
				tr_->getPosition().getY() + tr_->getHeight() / 2, 30 * tr_->getScale(), 30 * tr_->getScale());
		else
			bullet->addComponent<Transform>(tr_->getPosition().getX(), tr_->getPosition().getY() + tr_->getHeight() / 2,
				30 * tr_->getScale(), 30 * tr_->getScale());
		if (player->getComponent<Transform>()->getPosition().getX() >tr_->getPosition().getX())
			pc->setVelocity(Vector2D(2.2f, 0));
		else
			pc->setVelocity(Vector2D(-2.2f, 0));
		pc->setGravity(false);
		bullet->addComponent<Image>(&sdlutils().images().at("spores")); 
		bullet->addComponent<Bullet>(health->getElement(), ent_);
		attackingTime = SDL_GetTicks();
	}
}