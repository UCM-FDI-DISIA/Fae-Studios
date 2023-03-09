#include "Health.h"
#include "../Src/Entity.h"

void Health::die()
{
	if (ent_->hasComponent<PlayerInput>()) ent_->getComponent<PlayerAnimationComponent>()->setState(DIE);
	else ent_->getComponent<EnemyAnimationComponent>()->setState(DIE_ENEMY);
	dead = true;
} 

void Health::recall()
{
	if (lastSanctuary != nullptr) {
		Vector2D& newPos = ent_->getComponent<Transform>()->getPos();
		newPos = lastSanctuary->getComponent<Transform>()->getPos();
		actualLife = maxLife;
		cout << "vuelvo a santuario" << endl;
	}
	cout << "me muero para siempre" << endl;
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
