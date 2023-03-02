#include "EnemyMovement.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"

void EnemyMovement::initComponent()
{
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	playerTransform = player->getComponent<Transform>();

	trigger.x = transform->getPos().getX() + transform->getW(); trigger.y = transform->getPos().getY();
}

void EnemyMovement::MoveTriggers()
{
	SDL_Rect collider = transform->getRect();
	if (physics->getVelocity().getX() > 0) // Ajuste del trigger en función del movimiento del enemigo
		trigger.x = collider.x + collider.w;
	else
		trigger.x = collider.x - trigger.w;

	trigger.y = collider.y;
}

void EnemyMovement::detectPlayer()
{
	if (player != nullptr) {
		SDL_Rect playerRect = playerTransform->getRect();
		if (SDL_HasIntersection(&trigger, &playerRect)) playerDetected = true;
	}
}

void EnemyMovement::FollowPlayer()
{
	SDL_Rect collider = transform->getRect();
	SDL_Rect ott = playerTransform->getRect();
	bool lookingRight = physics->getVelocity().getX() > 0;
	if (lookingRight && abs(ott.x - (collider.x + collider.w)) > nearDistance ||
		!lookingRight && abs(ott.x + collider.w - collider.x) > nearDistance) {
		if ((double)ott.x - collider.x < 0) {
			//speed = { horizontalSpeed, speed.getY() };
			physics->getVelocity() = Vector2D(-horizontalSpeed, physics->getVelocity().getY());
		}
		else
			physics->getVelocity() = Vector2D(horizontalSpeed, physics->getVelocity().getY());
	
	}
	else {
		physics->getVelocity() = Vector2D(0, physics->getVelocity().getY());
	}
}

void EnemyMovement::ChangeDirection(const SDL_Rect& result)
{
	if (!playerDetected && result.w < transform->getW() * turningOffset) {
		if (abs(result.x - transform->getRect().x) < turningError) {
			physics->getVelocity() = {-1 * physics->getVelocity().getX(), physics->getVelocity().getY()};
		}
	}
}
