#include "Pivot.h"
#include "../sdlutils/InputHandler.h"
#include <math.h>

void Pivot::initComponent() {
	
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();	
}
void Pivot::update()
{
	Vector2D distance = playerTransform->getPosition() - transform->getPosition();	
	Vector2D aux= bossPhysics->getVelocity();

	if ((std::abs(distance.getX()) < 10.f && std::abs(distance.getY()) < 10.f))
	{
		if (!active) {
			if (num == 0)
			{
				bossPhysics->setVelocity({ 0,0.3 });
				playerTransform->setRotation(90);
			}
			else if (num == 1)
			{
				bossPhysics->setVelocity({ 0.3,0 });
				playerTransform->setRotation(90);
				bossPhysics->lookDirection(true);
			}
			else if (num == 2)
			{
				bossPhysics->setVelocity({ 0,-0.3 });
				playerTransform->setRotation(-90);
			}
			else if (num == 3)
			{
				bossPhysics->setVelocity({ -0.3,0 });
				playerTransform->setRotation(90);

				bossPhysics->lookDirection(false);
			}
			active = true;
		}
	}
	else active = false;
}
