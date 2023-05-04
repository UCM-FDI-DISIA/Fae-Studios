#include "AttractionComponent.h"
#include "FinalBossBehaviorComponent.h"
#include "PlayerInput.h"

void AttractionComponent::initComponent() {
	// Player
	player = mngr_->getPlayer();
	playerTransform = player->getComponent<Transform>();
	playerPhisics = player->getComponent<PhysicsComponent>();
	
	if (!player->getComponent<PlayerInput>()->isLight()) {
		playerPhisics->Stop();
		player->getComponent<PlayerInput>()->setBoolAttack(true);
		active = true;
	}

	// BlackHole
	blackHoleTransform = ent_->getComponent<Transform>();
}

void AttractionComponent::update() {

	if (!player->getComponent<PlayerInput>()->isLight()) {

		if (!active) {
			playerPhisics->Stop();
			player->getComponent<PlayerInput>()->setBoolAttack(true);
			active = true;
		}

		Vector2D dir = blackHoleTransform->getPosition() - playerTransform->getPosition();
		playerTransform->setPosition(Vector2D(playerTransform->getPosition() + dir.normalize()));

	}
	else {
		if (active) {
			active = false;
			playerPhisics->Resume();
			player->getComponent<PlayerInput>()->setBoolAttack(false);
		}
	}
	if (SDL_GetTicks() - spawnTime >= lifeTime) {
		bossBehaComp_->deleteBlackHoles();
		playerPhisics->Resume();
		player->getComponent<PlayerInput>()->setBoolAttack(false);
	}
}