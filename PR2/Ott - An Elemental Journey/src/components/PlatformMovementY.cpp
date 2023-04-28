#include "PlatformMovementY.h"
#include "../ecs/Entity.h"
#include "Transform.h"
void PlatformMovementY::initComponent()
{
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	physics->setVelocity(Vector2D(0, 1));
}

void PlatformMovementY::update()
{
	if (transform->getPosition().getY() * roomScale > max) {
		physics->setVelocity(Vector2D(0, -1));
	}
	else if (transform->getPosition().getY() * roomScale < min) {
		physics->setVelocity(Vector2D(0, 1));
	}

	/*deltaTime = SDL_GetTicks();
	physics->setVelocity(Vector2D(0, amplitude * (2 * M_PI) / time * cos((2 * M_PI) / time * deltaTime)));
	std::cout << ent_->getComponent<Transform>()->getPosition() << std::endl;*/
}