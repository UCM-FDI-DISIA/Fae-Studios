#include "PlatformMovementY.h"
#include "../ecs/Entity.h"
void PlatformMovementY::initComponent()
{
	physics = ent_->getComponent<PhysicsComponent>();
}

void PlatformMovementY::update()
{
	physics->setVelocity(Vector2D(0, amplitude * (2 * M_PI) / time * cos((2 * M_PI) / time * SDL_GetTicks())));
}