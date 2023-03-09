#include "Health.h"
#include "../Src/Entity.h"
#include "SlimeStates.h"
#include "Generations.h"

void Health::die()
{
	if (ent_->hasComponent<PlayerInput>()) ent_->getComponent<PlayerAnimationComponent>()->setState(DIE);
	else ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
	auto gen = ent_->getComponent<Generations>();
	// si la entidad muerta es un slime y no esta en su ultima gen manda a que se divida
	if (gen != nullptr && gen->getGeneration() > 1) ent_->getComponent<Generations>()->Divide();
	dead = true;
} 

void Health::recall()
{
	if (lastSanctuary != nullptr) {
		Vector2D& newPos = ent_->getComponent<Transform>()->getPos();
		newPos = lastSanctuary->getComponent<Transform>()->getPos();
		actualLife = maxLife;
	}
}

bool Health::recieveDamage(ecs::elements elem)
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) {
		PlayerAnimationComponent* pAnimRef = ent_->getComponent<PlayerAnimationComponent>();
		if (pAnimRef->isInvincible()) return false;
		pAnimRef->playerDamaged();
		actualLife -= ecs::ottMatrix[elem][this->elem];
	}
	else {
		if (!dead) {
			actualLife -= ecs::matrix[elem][this->elem];
			ent_->getComponent<EnemyAnimationComponent>()->damage();
		}
	}
	//startDamagedTime = SDL_GetTicks();
	if (!dead && actualLife <= 0) {
		die();
		return true;
	}
	else return false;
}

void Health::saveSactuary()
{
	lastSanctuary = mngr_->getCurrentInteraction();
	die();
}
