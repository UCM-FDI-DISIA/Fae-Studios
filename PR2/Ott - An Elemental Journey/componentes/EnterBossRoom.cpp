#include "EnterBossRoom.h"               
void EnterBossRoom::enterRoom() {
	//meter booleano para que solo detecte que has entrado una vez
	camera = mngr_->getHandler(ecs::CAMERA);
	player = mngr_->getHandler(ecs::PLAYER);
	if (resetTime) {
		timer = SDL_GetTicks();
		resetTime = false;
	}
	ent_->getComponent<VineManager>()->addVine();
}

void EnterBossRoom::update(){
	int aux = SDL_GetTicks() - timer;
	if (aux <= 1000) {
		if (camera != nullptr && player != nullptr) {
			camera->getComponent<CameraComponent>()->changeSize(300, 320);
			camera->getComponent<CameraComponent>()->camaraShake(true);
			player->getComponent<PlayerInput>()->setActive(false);

		}
	}
	else {
		if (camera != nullptr && player != nullptr) {
			camera->getComponent<CameraComponent>()->camaraShake(false);
			player->getComponent<PlayerInput>()->setActive(true);

		}
	}
}

void EnterBossRoom::initComponent() {
	blockDoor = ent_->getComponent<VineManager>()->getVine(); 
}