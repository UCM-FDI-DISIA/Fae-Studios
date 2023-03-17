#include "DamageArea.h"
void DamageArea::update()
{
	SDL_Rect pCol = pPhysics->getCollider();
	SDL_Rect dArea = tr->getRect();
	if (SDL_HasIntersection(&pCol, &dArea))
	{
		pHe->recieveDamage(element);
		pPhysics->setLastPos();
	}
}
void DamageArea::initComponent()
{
	tr = ent_->getComponent<Transform>();
	pPhysics = mngr_->getPlayer()->getComponent<PhysicsComponent>();
	pHe = mngr_->getPlayer()->getComponent<Health>();
}