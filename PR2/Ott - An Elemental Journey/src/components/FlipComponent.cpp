#include "FlipComponent.h"

void FlipComponent::initComponent() {
	transform = ent_->getComponent<Transform>();
}

void FlipComponent:: update() {
	if (SDL_GetTicks() - spawnTime >= lifeTime) {

		float rot = transform->getRotation() + 1.0f;
		transform->setRotation((int)rot % 360);
		spawnTime = SDL_GetTicks();
	}
}