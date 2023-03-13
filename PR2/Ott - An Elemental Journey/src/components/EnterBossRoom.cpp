#include "EnterBossRoom.h"  
#include "PhysicsComponent.h"
#include "FramedImage.h"
#include "EarthBossAnimationController.h"

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
		startFight();
		player->getComponent<PlayerInput>()->setActive(true);
	}
	else start = false;
}

void EnterBossRoom::startFight() {
	if (!added) {
		auto ph = earthBoss->getComponent<PhysicsComponent>();
		earthBoss->addComponent<FramedImage>(&sdlutils().images().at("animationWorm"), sdlutils().images().at("animationWorm").getNumRows(), sdlutils().images().at("animationWorm").getNumCols());
		earthBoss->addComponent<Health>(5, ecs::Earth, false);
		earthBoss->addComponent<EarthBossAnimationController>(anims::EARTH_ANIM);
		ph->setVelocity({ 0,0 });
		ph->lookDirection(true);
		added = true;
	}
}