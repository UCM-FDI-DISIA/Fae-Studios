#include "EnemyAttack.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"
#include "Health.h"
void EnemyAttack::initComponent() {
	player = mngr_->getPlayer();
	transform = ent_->getComponent<Transform>();
	physics = ent_->getComponent<PhysicsComponent>();
	health_ = ent_->getComponent<Health>();

	if (physics->getLookDirection())
		trigger.x = transform->getPos().getX() + transform->getW();
	else trigger.x = transform->getPos().getX() - trigger.w;
	trigger.y = transform->getPos().getY();
}

void EnemyAttack::MoveTriggers() {
	SDL_Rect collider = transform->getRect();
	if (physics->getLookDirection()) // Ajuste del trigger en funci�n del movimiento del enemigo
		trigger.x = collider.x + collider.w;
	else
		trigger.x = collider.x - trigger.w;

	trigger.y = collider.y;
}

void EnemyAttack::update() {
	if (health_->isDead()) {
		state == normal;
	}
	else {
		MoveTriggers();

		SDL_Rect playerRect = player->getComponent<Transform>()->getRect();
		SDL_Rect collider = physics->getCollider();

		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (state == normal && frameTime >= PHASE1_TIME && SDL_HasIntersection(&trigger, &playerRect)) {
			state = preparing;
			startAttackingTime = SDL_GetTicks();
		}
		else if (state == preparing && frameTime >= PHASE2_TIME) {
			state = attacking;
			startAttackingTime = SDL_GetTicks();
		}
		else if (state == attacking && frameTime >= PHASE3_TIME) {
			hasAttacked = true;
			state = afterAttack;
			startAttackingTime = SDL_GetTicks();
		}
		else if (state == afterAttack && frameTime >= PHASE4_TIME) {
			hasAttacked = false;
			state = normal;
			startAttackingTime = SDL_GetTicks();
		}
	}
}

bool EnemyAttack::requestAttack()
{
	SDL_Rect playerCollider = player->getComponent<Transform>()->getRect();
	return (!health_->isDead() && state == attacking && SDL_HasIntersection(&trigger, &playerCollider));
}

