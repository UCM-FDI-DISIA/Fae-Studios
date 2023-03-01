#include "EnemyAttack.h"
#include "../Src/Entity.h"

void EnemyAttack::initComponent() {
	transform = ent_->getComponent<Transform>();
	physics = ent_->getComponent<PhysicsComponent>();

	trigger.x = transform->getPos().getX() + transform->getW(); trigger.y = transform->getPos().getY();
}

void EnemyAttack::MoveTriggers() {
	SDL_Rect collider = transform->getRect();
	if (physics->getVelocity().getX() > 0) // Ajuste del trigger en función del movimiento del enemigo
		trigger.x = collider.x + collider.w;
	else
		trigger.x = collider.x - trigger.w;

	trigger.y = collider.y;
}

void EnemyAttack::update() {
	SDL_Rect playerRect = player->getComponent<PhysicsComponent>()->getCollider();
	SDL_Rect collider = physics->getCollider();

	int frameTime = SDL_GetTicks() - startAttackingTime;
	if (state == normal && frameTime >= PREPARING_TIME && SDL_HasIntersection(&collider, &playerRect)) {
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

