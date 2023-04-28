#include "WaterContainerComponent.h"
#include <iostream>
#include "Transform.h"
#include "FireBossComponent.h"
#include "waterDropComponent.h"
#include "Image.h"
WaterContainerComponent::WaterContainerComponent() 
{
}

void WaterContainerComponent::initComponent()
{
	tr = ent_->getComponent<Transform>();
	originalHeight = tr->getHeight();
	originalYpos = tr->getPosition().getY();
}

void WaterContainerComponent::update()
{
	tr->setHeight(originalHeight * currentFill / 100);
	tr->setPosition(Vector2D(tr->getPosition().getX(), originalYpos - tr->getHeight()));
	if (currentFill < 100) {
		currentFill += fillRate;
	}
}

void WaterContainerComponent::dropWater()
{
	auto& sdl = *SDLUtils::instance();
	
	for (int i = 0; i < 40; ++i) {
		int x = sdl.rand().nextInt(0, tr->getWidth());
		int y = sdl.rand().nextInt(0, tr->getHeight());
		int t = 10 + sdl.rand().nextInt(0, 20);
		auto gota = mngr_->addEntity(ecs::_grp_MAP);
		gota->addComponent<Transform>(Vector2D{ tr->getPosition().getX() + x, tr->getPosition().getY() + y }, t, t);
		gota->addComponent<Image>(&sdlutils().images().at("water"));
		gota->addComponent<waterDropComponent>();
	}
	currentFill = 0;
	auto tr = ent_->getComponent<Transform>();
	for (Entity* e : mngr_->getEntities(ecs::_grp_CHARACTERS)) {
		auto bossTr = e->getComponent<Transform>();
		SDL_Rect stunRect;
		stunRect.x = tr->getPosition().getX(); stunRect.y = tr->getPosition().getY() + tr->getHeight();
		stunRect.w = tr->getWidth(); stunRect.h = 1000;
		SDL_Rect bossRect = bossTr->getRect();
		if (SDL_HasIntersection(&stunRect, &bossRect) && e->hasComponent<FireBossComponent>()) {
			e->getComponent<FireBossComponent>()->stunBoss();
		}
	}
}

