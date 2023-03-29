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
	SDL_Rect result;
	if (!health_->isDead() && SDL_IntersectRect(&rect, &playerRect, &result)) {
		bool dir;
		if (result.x + result.w > rect.x + rect.w / 2) dir = true;
		else dir = false;
		player->getComponent<Health>()->recieveDamage(health_->getElement(), dir);

	}
}