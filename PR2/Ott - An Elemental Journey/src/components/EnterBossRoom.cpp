#include "EnterBossRoom.h"  
#include "PhysicsComponent.h"
#include "FramedImage.h"
#include "Transform.h"
#include "EarthBossManager.h"
#include "PhysicsComponent.h"

void EnterBossRoom::initComponent() {
	camera = mngr_->getCamera();
	player = mngr_->getPlayer();
	earthBoss = mngr_->getEarthBoss();
}

void EnterBossRoom::enterRoom() {
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
			player->getComponent<PhysicsComponent>()->Stop();
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
	if (aux > 2000 && aux <= 5000 && start) {
		startFight();
		player->getComponent<PhysicsComponent>()->Resume();
	}
	else start = false;
}

void EnterBossRoom::startFight() {
	if (!added) {
		earthBoss = mngr_->getEarthBoss();
		earthBoss->getComponent<EarthBossManager>()->initializeEntities();
		earthBoss->getComponent<EarthBossManager>()->isFighting(true);
		added = true;
	}
}