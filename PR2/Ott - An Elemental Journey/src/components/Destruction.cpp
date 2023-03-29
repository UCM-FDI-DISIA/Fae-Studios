#include "Destruction.h"

void Destruction::initComponent() {
	transform = ent_->getComponent<Transform>();
}

void Destruction::update() {
	SDL_Rect colliderBoss = bossTransform->getRect();
	SDL_Rect colliderObject = transform->getRect();
	
	SDL_Rect intersection;
	if (SDL_IntersectRect(&colliderBoss, &colliderObject, &intersection)) {
		map->destroyTile(room, index);
		ent_->setAlive(false);
	}
}