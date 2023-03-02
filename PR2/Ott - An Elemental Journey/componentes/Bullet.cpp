#include "Bullet.h"
#include "../Src/Entity.h"
void Bullet::initComponent()
{
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
