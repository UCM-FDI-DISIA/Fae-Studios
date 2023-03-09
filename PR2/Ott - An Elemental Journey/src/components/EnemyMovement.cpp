#include "EnemyMovement.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

void EnemyMovement::initComponent()
{
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	playerTransform = player->getComponent<Transform>();

	trigger.x = transform->getPosition().getX() + transform->getWidth(); trigger.y = transform->getPosition().getY();
	nearDistance = transform->getWidth() * 2;
}

void EnemyMovement::MoveTriggers()
{
	SDL_Rect collider = transform->getRect();
	if (physics->getVelocity().getX() > 0) // Ajuste del trigger en funci�n del movimiento del enemigo
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
	if (abs(ott.x - (collider.x + collider.w / 2)) > nearDistance) {
		if ((double)ott.x - collider.x < 0) {
			//speed = { horizontalSpeed, speed.getY() };
			physics->getVelocity() = Vector2D(-horizontalSpeed, physics->getVelocity().getY());
			physics->lookDirection(false);
		}
		else {
			physics->getVelocity() = Vector2D(horizontalSpeed, physics->getVelocity().getY());
			physics->lookDirection(true);
		}
	}
	else {
		physics->getVelocity() = Vector2D(0, physics->getVelocity().getY());
	}
}

void EnemyMovement::ChangeDirection(bool ground, const SDL_Rect& result)
{
	if (!playerDetected) {
		if (!ground) {
			int dir;
			if (physics->getLookDirection()) dir = -1;
			else dir = 1;
			physics->getVelocity() = { (float)dir, physics->getVelocity().getY() };
			physics->lookDirection(!physics->getLookDirection());
		}
		else if (result.w < transform->getRect().w * turningOffset)
		{
			if (abs(result.x - transform->getRect().x) < turningError) {
				physics->setVelocity({ -horizontalSpeed, physics->getVelocity().getY() });
				physics->lookDirection(false);
			}
			else {
				physics->setVelocity({ horizontalSpeed, physics->getVelocity().getY() });
				physics->lookDirection(true);
			}
		}
	}
	else if (!ground) {
		collided = true;
		playerDetected = false;
	} 
}


void EnemyMovement::update() {
	MoveTriggers();
	if (playerDetected && !collided) FollowPlayer();
	detectPlayer();
	collided = false;
}
