#include "Health.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "PlayerAnimationComponent.h"
#include "../game/Elements.h"

void Health::die()
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) ent_->getComponent<PlayerAnimationComponent>()->setState(DIE);
	else ent_->setAlive(false);
}

void Health::recall()
{
	if (lastSanctuary != nullptr) {
		Vector2D newPos = ent_->getComponent<Transform>()->getPosition();
		newPos = lastSanctuary->getComponent<Transform>()->getPosition(); //?????
		actualLife = maxLife;
		//cout << "vuelvo a santuario" << endl;
	}
	//cout << "me muero para siempre" << endl;
}

bool Health::recieveDamage(ecs::elements elem)
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) {
		PlayerAnimationComponent* pAnimRef = ent_->getComponent<PlayerAnimationComponent>();
		if (pAnimRef->isInvincible()) return false;
		pAnimRef->playerDamaged();
	}
	//if() Añadir daño dependiendo de la entidad
	actualLife -= elementsInfo::matrix[elem][elem];
	//startDamagedTime = SDL_GetTicks();
	if (actualLife <= 0) {
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
