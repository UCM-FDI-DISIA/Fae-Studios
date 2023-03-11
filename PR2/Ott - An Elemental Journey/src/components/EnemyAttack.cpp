#include "EnemyAttack.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"

void EnemyAttack::initComponent() {
	player = mngr_->getPlayer();
	transform = ent_->getComponent<Transform>();
	physics = ent_->getComponent<PhysicsComponent>();

	trigger.x = transform->getPosition().getX() + transform->getWidth(); trigger.y = transform->getPosition().getY();
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

bool EnemyAttack::requestAttack() {
	SDL_Rect playerCollider = physics->getCollider();
	return (state == attacking && SDL_HasIntersection(&trigger, &playerCollider));
}

