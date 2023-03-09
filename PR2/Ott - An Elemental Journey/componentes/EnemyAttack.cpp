#include "EnemyAttack.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"
void EnemyAttack::initComponent() {
	player = mngr_->getPlayer();
	transform = ent_->getComponent<Transform>();
	physics = ent_->getComponent<PhysicsComponent>();

	if (physics->getLookDirection())
		trigger.x = transform->getPos().getX() + transform->getW();
	else trigger.x = transform->getPos().getX() - trigger.w;
	trigger.y = transform->getPos().getY();
}

void EnemyAttack::MoveTriggers() {
	SDL_Rect collider = transform->getRect();
	if (physics->getLookDirection()) // Ajuste del trigger en función del movimiento del enemigo
		trigger.x = collider.x + collider.w;
	else
		trigger.x = collider.x - trigger.w;

	trigger.y = collider.y;
}

void EnemyAttack::update() {
	MoveTriggers();

	SDL_Rect playerRect = player->getComponent<Transform>()->getRect();
	SDL_Rect collider = physics->getCollider();

	int frameTime = SDL_GetTicks() - startAttackingTime;
	if (state == normal && frameTime >= PREPARING_TIME && SDL_HasIntersection(&trigger, &playerRect)) {
		state = preparing;
		startAttackingTime = SDL_GetTicks();
	}
	else if (state == preparing && frameTime >= PREPARING_TIME) {
		state = attacking;
		startAttackingTime = SDL_GetTicks();
	}
	else if (state == attacking && frameTime >= ATTACKING_TIME / 2) {
		state = afterAttack;
		startAttackingTime = SDL_GetTicks();
	}
	else if (state == afterAttack && frameTime >= ATTACKING_TIME / 2) {
		state = normal;
		startAttackingTime = SDL_GetTicks();
	}
}

bool EnemyAttack::requestAttack()
{
	SDL_Rect playerCollider = player->getComponent<Transform>()->getRect();
	return (state == attacking && SDL_HasIntersection(&trigger, &playerCollider));
}

