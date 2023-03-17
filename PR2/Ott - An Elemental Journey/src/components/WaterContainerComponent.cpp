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
	currentFill = 0;
	auto tr = ent_->getComponent<Transform>();
	auto bossTr = fireBoss->getComponent<Transform>();
	SDL_Rect stunRect;
	stunRect.x = tr->getPosition().getX(); stunRect.y = tr->getPosition().getY();
	stunRect.w = tr->getWidth(); stunRect.h = (bossTr->getPosition().getY() + bossTr->getHeight())- tr->getPosition().getY();
	SDL_Rect bossRect = bossTr->getRect();
	if (SDL_HasIntersection(&stunRect, &bossRect)) {
		fireBoss->getComponent<FireBossComponent>()->stunBoss();
	}
}

