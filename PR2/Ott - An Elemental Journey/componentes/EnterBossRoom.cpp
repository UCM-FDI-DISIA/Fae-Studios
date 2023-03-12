#include "EnterBossRoom.h"               
void EnterBossRoom::enterRoom() {
	cout << "entrando" << endl;
	camera = mngr_->getHandler(ecs::CAMERA);
	player = mngr_->getHandler(ecs::PLAYER);
	if (resetTime) {
		timer = SDL_GetTicks();
		resetTime = false;
	}
	//ent_->getComponent<AddVine>()->getVine()->addComponent<ImageVine>(tx_);
	ent_->getComponent<AddVine>()->getVine()->addComponent<GrowVine>(ent_->getComponent<AddVine>()->getPosFin());
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
