#include "WaterContainerComponent.h"
#include <iostream>
#include "Transform.h"
#include "FireBossComponent.h"
#include "Image.h"
WaterContainerComponent::WaterContainerComponent(Entity* Ref) : fireBoss(Ref)
{
}

void WaterContainerComponent::initComponent()
{
	auto tr = ent_->getComponent<Transform>();
	originalHeight = tr->getHeight();
	originalYpos = tr->getPosition().getY();
}

void WaterContainerComponent::update()
{
	auto tr = ent_->getComponent<Transform>();
	tr->setHeight(originalHeight * currentFill / 100);
	tr->setPosition(Vector2D(tr->getPosition().getX(), originalYpos - tr->getHeight()));
	if (currentFill < 100) {
		currentFill += fillRate;
	}
}

void WaterContainerComponent::dropWater()
{
	std::cout << "Cae agua" << std::endl;
	currentFill = 0;
	auto tr = ent_->getComponent<Transform>();
	auto bossTr = fireBoss->getComponent<Transform>();
	SDL_Rect stunRect;
	stunRect.x = tr->getPosition().getX(); stunRect.y = tr->getPosition().getY() + tr->getHeight();
	stunRect.w = tr->getWidth(); stunRect.h = 1000;
	SDL_Rect bossRect = bossTr->getRect();
	if (SDL_HasIntersection(&stunRect, &bossRect)) {
		std::cout << "Boss mojado" << std::endl;
		fireBoss->getComponent<FireBossComponent>()->stunBoss();
	}
}

