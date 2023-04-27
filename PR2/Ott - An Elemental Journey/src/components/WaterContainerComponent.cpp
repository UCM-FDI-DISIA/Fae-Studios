#include "WaterContainerComponent.h"
#include <iostream>
#include "Transform.h"
#include "FireBossComponent.h"
#include "Image.h"
WaterContainerComponent::WaterContainerComponent() 
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
	for (Entity* e : mngr_->getEntities(ecs::_grp_CHARACTERS)) {
		auto bossTr = e->getComponent<Transform>();
		SDL_Rect stunRect;
		stunRect.x = tr->getPosition().getX(); stunRect.y = tr->getPosition().getY() + tr->getHeight();
		stunRect.w = tr->getWidth(); stunRect.h = 1000;
		SDL_Rect bossRect = bossTr->getRect();
		if (SDL_HasIntersection(&stunRect, &bossRect) && e->hasComponent<FireBossComponent>()) {
			std::cout << "Boss mojado" << std::endl;
			e->getComponent<FireBossComponent>()->stunBoss();
		}
	}
}

