#include "WaterBossAttack.h"
void WaterBossAttack::initComponent() {
	transform = ent_->getComponent<Transform>();
	ott = mngr_->getPlayer();
	ottTransform = ott->getComponent<Transform>();
	ottHealth = ott->getComponent<Health>();
}

void WaterBossAttack::update() {
	SDL_Rect colliderOtt = ottTransform->getRect();
	SDL_Rect colliderObject = transform->getRect();

	SDL_Rect intersection;
	if (SDL_IntersectRect(&colliderOtt, &colliderObject, &intersection)) {
	
		ottHealth->killHealth();
	}
}