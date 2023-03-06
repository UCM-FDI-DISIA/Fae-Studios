#include "DisableOnExit.h"
#include "../ecs/Entity.h"

void DisableOnExit::initComponent()
{
	transform = ent_->getComponent<Transform>();
	assert(transform != nullptr);
}

void DisableOnExit::update() {
	if (ent_->isAlive() && (transform->getPosition().getX() < 0 || transform->getPosition().getX() > sdlutils().width() ||
		transform->getPosition().getY() < 0 || transform->getPosition().getY() > sdlutils().height()))
		ent_->setAlive(false); //Si la entidad se va por los bordes se desactiva
}
