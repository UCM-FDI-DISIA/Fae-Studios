#include "AttractionComponent.h"

void AttractionComponent::initComponent() {
	// Player
	player = mngr_->getPlayer();
	playerTransform = player->getComponent<Transform>();
	playerPhisics = player->getComponent<PhysicsComponent>();
	playerPhisics->Stop();

	// BlackHole
	blackHoleTransform = ent_->getComponent<Transform>();
}

void AttractionComponent::update() {
	Vector2D dir = blackHoleTransform->getPosition() - playerTransform->getPosition();
	playerTransform->setPosition(Vector2D(playerTransform->getPosition() + dir.normalize()));

	if (SDL_GetTicks() - spawnTime >= lifeTime) {
		ent_->setAlive(false); 
		playerPhisics->Resume();
	}
}