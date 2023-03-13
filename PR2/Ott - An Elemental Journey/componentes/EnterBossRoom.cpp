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
			start = true;
		}
		if (col == 7) col = 0;
		else ++col;
	}
	else {
		if (camera != nullptr && player != nullptr) {
			camera->getComponent<CameraComponent>()->camaraShake(false);
			//player->getComponent<PlayerInput>()->setActive(true);

		}
	}
	if (aux >1000 && aux <= 3000 && start) {
		mngr_->addBossEarth();
		player->getComponent<PlayerInput>()->setActive(true);
	}
	else start = false;
}

void EnterBossRoom::initComponent() {
	blockDoor = ent_->getComponent<VineManager>()->getVine(); 
//}
//void EnterBossRoom::render() {
//		SDL_Rect dest;
//	//	dest.x= 7753;
//		//dest.y = 1897;
//		dest.x = 500;
//		dest.y = 2000;
//		dest.w = 453;
//		dest.h = 250;
//	anim->render(dest);
//	if (start) {
//		anim->renderFrame(dest, 0, col);
//	}
}