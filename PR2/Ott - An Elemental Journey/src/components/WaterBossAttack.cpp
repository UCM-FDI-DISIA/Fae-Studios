#include "WaterBossAttack.h"
void WaterBossAttack::initComponent() {
	transform = ent_->getComponent<Transform>();
	ott = mngr_->getPlayer();
	ottTransform = ott->getComponent<Transform>();
	ottHealth = ott->getComponent<Health>();
}

void WaterBossAttack::update() {
	std::cout << "ESTOY VIVO " << transform->getPosition().getX() << " " << transform->getPosition().getY() << std::endl;
	SDL_Rect colliderOtt = ottTransform->getRect();
	SDL_Rect colliderObject = transform->getRect();

	colliderObject.y = colliderObject.y + 150;
	colliderObject.w -= 150;
	colliderObject.h -= 300;

	SDL_Rect intersection;
	if (SDL_IntersectRect(&colliderOtt, &colliderObject, &intersection)) {
	
		ottHealth->killHealth();
	}
}