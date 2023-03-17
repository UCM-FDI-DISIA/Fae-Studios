#include "WaterVineComponent.h"
#include "Transform.h"
#include "WaterContainerComponent.h"
#include "../ecs/Manager.h"
#include "Bullet.h"
WaterVineComponent::WaterVineComponent(Entity* ref) : waterTankRef(ref)
{
	
}

void WaterVineComponent::initComponent()
{
	originalHeight = ent_->getComponent<Transform>()->getHeight();
	pickSpawnLocation();
}

void WaterVineComponent::update()
{
	auto tr = ent_->getComponent<Transform>();
	auto WaterTr = waterTankRef->getComponent<WaterContainerComponent>();
	tr->setHeight(originalHeight * WaterTr->getCurrentFill() / 100);
	for (Entity* e : mngr_->getEntities(ecs::_grp_PROYECTILES)) {
		if (e->hasComponent<Bullet>()) {
			auto bulletComp = e->getComponent<Bullet>();
			int elem = bulletComp->getElem();
			auto inst = bulletComp->getInstigator();
			auto containerComp = waterTankRef->getComponent<WaterContainerComponent>();
			SDL_Rect r1 = tr->getRect(); SDL_Rect r2 = e->getComponent<Transform>()->getRect();
			bool col = SDL_HasIntersection(&r1, &r2);
			if (elem == ecs::Fire && inst == mngr_->getPlayer() && containerComp->getCurrentFill()>= 100 && col) containerComp->dropWater();
		}
	}
}

void WaterVineComponent::pickSpawnLocation()
{
	auto WaterTr = waterTankRef->getComponent<Transform>();
	auto tr = ent_->getComponent<Transform>();
	int n = rand() % 2;
	if (n == 0) tr->setPosition(Vector2D(WaterTr->getPosition().getX(), WaterTr->getPosition().getY()));
	else tr->setPosition(Vector2D(WaterTr->getPosition().getX() + WaterTr->getWidth(), WaterTr->getPosition().getY()));
}
