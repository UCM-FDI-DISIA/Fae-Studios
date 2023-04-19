#include "PlatformMovementY.h"
#include "../ecs/Entity.h"
#include "Transform.h"
void PlatformMovementY::initComponent()
{
	physics = ent_->getComponent<PhysicsComponent>();
}

void PlatformMovementY::update()
{
	deltaTime = SDL_GetTicks();
	physics->setVelocity(Vector2D(0, amplitude * (2 * M_PI) / time * cos((2 * M_PI) / time * deltaTime)));
	std::cout << ent_->getComponent<Transform>()->getPosition() << std::endl;
}