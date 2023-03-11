#include "Health.h"
#include "../Src/Entity.h"

void Health::die()
{
	if (ent_->hasComponent<PlayerAnimationComponent>()) ent_->getComponent<PlayerAnimationComponent>()->setState(DIE);
	else ent_->setAlive(false);
}

void Health::initComponent() {
	pAnim_ = ent_->getComponent<PlayerAnimationComponent>();
	image = ent_->getComponent<HealthImage>();
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

bool Health::recieveDamage(ecs::elements el)
{
	if (pAnim_->isInvincible()) return false;
	pAnim_->playerDamaged();
	//if() Añadir daño dependiendo de la entidad
	int damage = elementsInfo::ottMatrix[el][elem];
	actualLife -= damage;
	if (damage == 0) {
		if (image->setWeak()) damage = 1;
	}
	image->damage(damage);
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
