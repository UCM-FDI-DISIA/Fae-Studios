#include "EnterBossRoom.h"               
void EnterBossRoom::enterRoom() {
	camera = mngr_->getCamera();
	player = mngr_->getPlayer();
	if (resetTime) {
		timer = SDL_GetTicks();
		resetTime = false;
	}
	ent_->getComponent<VineManager>()->addVine();
}

void EnterBossRoom::update() {
	int aux = SDL_GetTicks() - timer;
	if (aux <= 1000) {
		if (camera != nullptr && player != nullptr) {
			camera->getComponent<CameraComponent>()->cameraShake(true);
			player->getComponent<PlayerInput>()->setActive(false);
			start = true;
		}
		if (col == 7) col = 0;
		else ++col;
	}
	else {
		if (camera != nullptr && player != nullptr) {
			camera->getComponent<CameraComponent>()->cameraShake(false);
		}
	}
	if (aux > 1000 && aux <= 3000 && start) {
		//mngr_->addBossEarth();
		player->getComponent<PlayerInput>()->setActive(true);
	}
	else start = false;
}
