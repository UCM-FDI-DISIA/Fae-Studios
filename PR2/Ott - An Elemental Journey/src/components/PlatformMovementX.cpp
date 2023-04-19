#include "PlatformMovementX.h"
#include "../ecs/Entity.h"
void PlatformMovementX::initComponent()
{
	physics = ent_->getComponent<PhysicsComponent>();
}

void PlatformMovementX::update()
{
	physics->setVelocity(Vector2D(amplitude * (2 * M_PI) / time * cos((2 * M_PI) / time * SDL_GetTicks()), 0));
}