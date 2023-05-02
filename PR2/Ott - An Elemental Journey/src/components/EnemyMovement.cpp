#include "EnemyMovement.h"
#include "Health.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "EnemyAttack.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

void EnemyMovement::initComponent()
{
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
	transform = ent_->getComponent<Transform>();
	playerCollider = player->getComponent<PhysicsComponent>();
	health_ = ent_->getComponent<Health>();
	image_ = ent_->getComponent<FramedImage>();
	eAttack_ = ent_->getComponent<EnemyAttack>();

	trigger.x = transform->getPosition().getX() + transform->getWidth(); trigger.y = transform->getPosition().getY();
	nearDistance = eAttack_->nearDistance();
}

void EnemyMovement::MoveTriggers()
{
	SDL_Rect collider = physics->getCollider();
	if (physics->getVelocity().getX() > 0) // Ajuste del trigger en funci�n del movimiento del enemigo
		trigger.x = collider.x + collider.w;
	else
		trigger.x = collider.x - trigger.w;

	trigger.y = collider.y;
}

void EnemyMovement::detectPlayer()
{
	if (player != nullptr && eAttack_->getState()!= eAttack_->attacking && eAttack_->getState() != eAttack_->preparing && eAttack_->getState() != eAttack_->laying) {
		SDL_Rect playerRect = playerCollider->getCollider();
		if (SDL_HasIntersection(&trigger, &playerRect)) playerDetected = true;
	}
}

void EnemyMovement::FollowPlayer()
{
	SDL_Rect collider = physics->getCollider();
	SDL_Rect ott = playerCollider->getCollider();
	if (eAttack_->getState() == eAttack_->normal && ((physics->getLookDirection() && ott.x - (collider.x + collider.w / 2) > nearDistance) ||
		(!physics->getLookDirection() && (collider.x + collider.w / 2) - (ott.x + ott.w) > nearDistance))) {
		if ((double)ott.x - collider.x < 0) {
			//speed = { horizontalSpeed, speed.getY() };
			physics->getVelocity() = Vector2D(-horizontalSpeed, physics->getVelocity().getY());
			physics->lookDirection(false);
			image_->flipTexture(true);
		}
		else {
			physics->getVelocity() = Vector2D(horizontalSpeed, physics->getVelocity().getY());
			physics->lookDirection(true);
			image_->flipTexture(false);
		}
	}
	else {
		physics->getVelocity() = Vector2D(0, physics->getVelocity().getY());
		if (eAttack_->getState() == eAttack_->normal) {
			physics->lookDirection(!((double)ott.x - collider.x < 0));
			image_->flipTexture(!physics->getLookDirection());
		}
	}
}

void EnemyMovement::ChangeDirection(bool ground, const SDL_Rect& result)
{
    if(eAttack_->getState() != eAttack_->attacking && eAttack_->getState() != eAttack_->preparing && eAttack_->getState() != eAttack_->laying){
	    if (!playerDetected) {
		    if (!ground) {
			    int dir;
			    if (physics->getLookDirection()) dir = -1;
			    else dir = 1;
			    physics->getVelocity() = { (float)dir, physics->getVelocity().getY() };
			    image_->flipTexture(physics->getLookDirection());
			    physics->lookDirection(!physics->getLookDirection());
		    }
		    else if (result.w < physics->getCollider().w * turningOffset)
		    {
			    if (abs(result.x - physics->getCollider().x) < turningError) {
				    physics->setVelocity({ -horizontalSpeed, physics->getVelocity().getY() });
				    physics->lookDirection(false);
				    image_->flipTexture(true);
			    }
			    else {
				    physics->setVelocity({ horizontalSpeed, physics->getVelocity().getY() });
				    physics->lookDirection(true);
				    image_->flipTexture(false);
			    }
		    }
	    }
	    else if (!ground) {
		    collided = true;
		    playerDetected = false;
	    }
    }
}


void EnemyMovement::update() {
	if (!health_->isDead()) {
		MoveTriggers();
		if (playerDetected && !collided)
			if (eAttack_->getState() != eAttack_->attacking && eAttack_->getState() != eAttack_->preparing && eAttack_->getState() != eAttack_->laying) FollowPlayer();
			else physics->setVelocity({ 0,0 });
		detectPlayer();
		collided = false;
		moving = abs(physics->getVelocity().getX()) > 0;
	}
	else physics->setVelocity({ 0,0 });
}
