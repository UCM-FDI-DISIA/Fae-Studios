#include "Bullet.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"

void Bullet::initComponent()
{
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
}

void Bullet::update() //Faltan colisiones con las paredes
{
	SDL_Rect playerCollider = player->getComponent<PhysicsComponent>()->getCollider();
	SDL_Rect collider = physics->getCollider();
	if (SDL_HasIntersection(&playerCollider, &collider)) {
		player->getComponent<Health>()->recieveDamage(elem);
		ent_->setAlive(false);
	}
}
