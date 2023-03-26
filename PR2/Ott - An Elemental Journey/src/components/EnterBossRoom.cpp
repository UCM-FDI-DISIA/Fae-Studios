#include "EnterBossRoom.h"  
#include "PhysicsComponent.h"
#include "FramedImage.h"
#include "Transform.h"
#include "EarthBossManager.h"
#include "PhysicsComponent.h"
#include "EarthBossAttack.h"
#include "../states/GameStateMachine.h"
#include "../states/PlayState.h"

void EnterBossRoom::initComponent() {
	camera = mngr_->getCamera();
	player = mngr_->getPlayer();
	earthBoss = mngr_->getEarthBoss();
}

void EnterBossRoom::blockDoors() {
	auto state = static_cast<PlayState*>(stateMachine().currentState());
	map = state->getMap();

	// hacer que crezcan dos vines con collider
	SDL_Rect vine_Rect1 = { bossRoom.x + 30*3, bossRoom.y + bossRoom.h, 30, bossRoom.h };
	Vector2D finPosVine1 = Vector2D(bossRoom.x +30*3, bossRoom.y);
	blockEnter = mngr_->addEntity(ecs::_grp_GROUND);
	blockEnter->addComponent<Transform>(vine_Rect1);
	blockEnter->addComponent<ImageVine>(&sdlutils().images().at("vine"), 0, false);
	blockEnter->addComponent<GrowVine>(finPosVine1, 2, -1, "vertical", false);
	blockEnter->addComponent<EarthBossAttack>();
	blockEnter->getComponent<GrowVine>()->isGrowing(true);
	SDL_Rect collision1 = { (bossRoom.x + 30 * 3) - 10, bossRoom.y, 5, bossRoom.h };
	map->addCollision("6", collision1);

	SDL_Rect vine_Rect2 = { bossRoom.x + (bossRoom.w/2)*1.65, bossRoom.y + bossRoom.h, 30, bossRoom.h };
	Vector2D finPosVine2 = Vector2D(bossRoom.x + (bossRoom.w / 2) * 1.65, bossRoom.y);
	blockExit = mngr_->addEntity(ecs::_grp_GROUND);
	blockExit->addComponent<Transform>(vine_Rect2);
	blockExit->addComponent<ImageVine>(&sdlutils().images().at("vine"), 0, false);
	blockExit->addComponent<GrowVine>(finPosVine2, 2, -1, "vertical", false);
	blockExit->addComponent<EarthBossAttack>();
	blockExit->getComponent<GrowVine>()->isGrowing(true);
	SDL_Rect collision2 = { (bossRoom.x + (bossRoom.w / 2) * 1.65)+10, bossRoom.y, 5, bossRoom.h };
	map->addCollision("6", collision2);
}

void EnterBossRoom::enterRoom() {
	if (resetTime) {
		timer = SDL_GetTicks();
		resetTime = false;
		startShaking = true;
	    bossRoom.w = sdlutils().width() + 1;
		bossRoom.x -= 150;
		bossRoom.y -= 100;
		bossRoom.h += 150;
		camera->getComponent<CameraComponent>()->setBounds(bossRoom);
		blockDoors();
	}
}

void EnterBossRoom::update() {
	if (startShaking) {
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
		if (start && aux > 2000 && aux <= 5000) {
			startFight();
			startShaking = false;
		}

	}
}

void EnterBossRoom::startFight() {
	if (!added) {
		earthBoss = mngr_->getEarthBoss();
		earthBoss->getComponent<EarthBossManager>()->initializeEntities();
		earthBoss->getComponent<EarthBossManager>()->isFighting(true);
		added = true;
	}
}