#include "waterDropComponent.h"
#include "../ecs/Entity.h"
#include "Transform.h"
waterDropComponent::waterDropComponent()
{
}

void waterDropComponent::initComponent()
{
	tr = ent_->getComponent<Transform>();
	startTime = SDL_GetTicks();
}

void waterDropComponent::update()
{
	if (SDL_GetTicks() - startTime < lifeTime) {
		if (fallSpeed < maxSpeed) fallSpeed += acceleration;
		tr->setPosition(tr->getPosition() + Vector2D{ 0, fallSpeed });
	}
	else ent_->setActive(false);
}
