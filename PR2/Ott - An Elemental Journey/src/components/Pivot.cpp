#include "Pivot.h"
#include "../sdlutils/InputHandler.h"
#include <math.h>
#include "MapComponent.h"

void Pivot::initComponent() {
	
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();	
}
void Pivot::update()
{
	SDL_Rect colliderBoss = playerTransform->getRect();
	SDL_Rect colliderObject = transform->getRect();

	SDL_Rect intersection;
	if (SDL_IntersectRect(&colliderBoss, &colliderObject, &intersection)) {
	
		if (!active) {
			if (num == 0)
			{
				bossPhysics->setVelocity({ 0,0.3 });
				playerTransform->setRotation(90);
			}
			else if (num == 1)
			{
				bossPhysics->setVelocity({ 0.3,0 });
				if (playerTransform->getRotation() == 90)
				{
					playerTransform->setRotation(-90);
				}
				else{

					playerTransform->setRotation(+90);
				}

				bossPhysics->lookDirection(true);

			}
			else if (num == 2 && !player->getComponent<Acceleration>()->getWaiting())
			{
				bossPhysics->setVelocity({ 0,-0.3 });
				playerTransform->setRotation(-90);
				//player->getComponent<Acceleration>()->setWaiting(true,1);
			}
			else if (num == 3)
			{
				bossPhysics->setVelocity({ 0,-0.3 });
				playerTransform->setRotation(-90);

			}
			else if (num == 4)
			{
				bossPhysics->setVelocity({ 0.3,0 });
				playerTransform->setRotation(+90);
				//player->getComponent<Acceleration>()->setWaiting(true,2);

			}
			else if (num == 5) {
				player->setAlive(false);
				map->getComponent<MapComponent>()->setBossCompleted(ecs::Water);
			}
			active = true;
		}
	}
	else active = false;

}
