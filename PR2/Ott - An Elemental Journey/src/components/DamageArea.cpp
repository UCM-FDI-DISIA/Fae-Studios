#include "DamageArea.h"
#include "Bullet.h"
#include "PlayerInput.h"
#include "../ecs/Entity.h"
void DamageArea::update()
{
	SDL_Rect pCol = pPhysics->getCollider();
	SDL_Rect dArea = tr->getRect();
	if (SDL_HasIntersection(&pCol, &dArea))
	{
		//necesita la dirección de algo
		pHe->recieveDamage(element, !(pPhysics->getLookDirection()));
		pPhysics->setLastPos();
	}
	std::vector <Entity*> fireBall = mngr_->getEntities(ecs::_grp_PROYECTILES);
	if (!lava)
	{
		for (Entity* f : fireBall)
		{
			SDL_Rect r3 = f->getComponent<Transform>()->getRect();
			Bullet* b = f->getComponent<Bullet>();
			if (b!= nullptr && SDL_HasIntersection(&r3, &dArea) && b->getInstigator()->hasComponent<PlayerInput>())
			{
				if (bossBehaComp_ == nullptr)ent_->setAlive(false);
				else bossBehaComp_->deleteSpikeFromVec(ent_);
				f->setAlive(false);
			}
		}
	}
	if (bossBehaComp_ != nullptr && SDL_GetTicks() - spawnTime >= lifeTime) {

		//Se mata pasados unos segundos
		bossBehaComp_->deleteSpikes();
	}
}
void DamageArea::initComponent()
{
	tr = ent_->getComponent<Transform>();
	pPhysics = mngr_->getPlayer()->getComponent<PhysicsComponent>();
	pHe = mngr_->getPlayer()->getComponent<Health>();
	spawnTime = SDL_GetTicks();
}