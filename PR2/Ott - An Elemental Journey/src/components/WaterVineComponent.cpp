#include "WaterVineComponent.h"
#include "Transform.h"
#include "WaterContainerComponent.h"

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
}

void WaterVineComponent::pickSpawnLocation()
{
	auto WaterTr = waterTankRef->getComponent<Transform>();
	auto tr = ent_->getComponent<Transform>();
	int n = rand() % 2;
	if (n == 0) tr->setPosition(Vector2D(WaterTr->getPosition().getX(), WaterTr->getPosition().getY()));
	else tr->setPosition(Vector2D(WaterTr->getPosition().getX() + WaterTr->getWidth(), WaterTr->getPosition().getY()));
}
