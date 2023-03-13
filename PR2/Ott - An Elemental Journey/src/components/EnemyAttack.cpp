#include "EnemyAttack.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include "Health.h"
#include "EnemyAnimationController.h"
#include "EnemyShootingAttack.h"
#include "EnemyMeleeAttack.h"
#include "../states/PlayState.h"
#include "../states/GameStateMachine.h"

void EnemyAttack::initComponent() {
	player = mngr_->getPlayer();
	transform = ent_->getComponent<Transform>();
	physics = ent_->getComponent<PhysicsComponent>();
	health_ = ent_->getComponent<Health>();

	SDL_Rect collider = physics->getCollider();
	trigger.h = collider.h;
	if (trigger.w == 0) {
		SDL_Rect rect = transform->getRect();
		trigger.w = rect.w + rect.x - collider.x - collider.w;
	}

	if (physics->getLookDirection())
		trigger.x = transform->getPosition().getX() + transform->getWidth();
	else trigger.x = transform->getPosition().getX() - trigger.w;
	trigger.y = transform->getPosition().getY();
}

void EnemyAttack::MoveTriggers() {
	SDL_Rect collider = physics->getCollider();
	if (physics->getLookDirection()) // Ajuste del trigger en función del movimiento del enemigo
		trigger.x = collider.x + collider.w;
	else
		trigger.x = collider.x - trigger.w;

	trigger.y = collider.y;
}


void EnemyAttack::SetRefs(EnemyAnimationComponent* a, EnemyShootingAttack* s, EnemyMeleeAttack* m) {
	eAnim_ = a;
	shootingAttack_ = s;
	meleeAttack_ = m;
};



void EnemyAttack::update() {
	if (health_->isDead()) {
		state == normal;
	}
	else {
		MoveTriggers();

		SDL_Rect playerRect = player->getComponent<PhysicsComponent>()->getCollider();
		SDL_Rect collider = physics->getCollider();

		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (state == normal && frameTime >= TIME_BETWEEN_ATTACKS && SDL_HasIntersection(&trigger, &playerRect)) {
			state = preparing;
			eAnim_->setState(PREPARE_ATTACK_ENEMY);
			startAttackingTime = SDL_GetTicks();
		}
		else if (state == preparing && eAnim_->getState() != PREPARE_ATTACK_ENEMY) {
			state = attacking;
			startAttackingTime = SDL_GetTicks();
		}
		else if (state == attacking && eAnim_->getState() != ATTACK_ENEMY) {
			state = afterAttack;
			startAttackingTime = SDL_GetTicks();
		}
		else if (state == afterAttack && eAnim_->getState() != AFTER_ATTACK_ENEMY) {
			state = normal;
			startAttackingTime = SDL_GetTicks();
		}
	}
}

bool EnemyAttack::requestAttack()
{
	SDL_Rect playerCollider = player->getComponent<PhysicsComponent>()->getCollider();
	return (!health_->isDead() && SDL_HasIntersection(&trigger, &playerCollider));
}

void EnemyAttack::Attack() {
	if (shootingAttack_ != nullptr) shootingAttack_->Attack();
	else meleeAttack_->Attack();
}

