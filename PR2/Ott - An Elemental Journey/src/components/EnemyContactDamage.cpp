#include "EnemyContactDamage.h"
#include "../ecs/Entity.h"
#include "Health.h"

void EnemyContactDamage::initComponent() {
	collider = ent_->getComponent<PhysicsComponent>();
	playerCollider = mngr_->getPlayer()->getComponent<PhysicsComponent>();
	player = mngr_->getPlayer();
	health_ = ent_->getComponent<Health>();
}



void EnemyContactDamage::update() {
	SDL_Rect rect = collider->getCollider();
	SDL_Rect playerRect = playerCollider->getCollider();

	if (SDL_HasIntersection(&rect, &playerRect)) player->getComponent<Health>()->recieveDamage(health_->getElement());
}