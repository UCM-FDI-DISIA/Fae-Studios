#include "FirePillarComponent.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"
FirePillarComponent::FirePillarComponent()
{
}

void FirePillarComponent::initComponent()
{
	tr = ent_->getComponent<Transform>();
	startVerticalPos = tr->getPosition().getY();
}

void FirePillarComponent::update()
{
	auto pos = tr->getPosition();
	if (countDown == -1 && startVerticalPos - tr->getPosition().getY()  >= tr->getHeight() ) {
		countDown = SDL_GetTicks();
	}
	else if (countDown == -1 && startVerticalPos - tr->getPosition().getY() < tr->getHeight()) tr->setPosition(Vector2D(pos.getX(), pos.getY() - speed));
	else if (tr->getPosition().getY() > startVerticalPos) ent_->setAlive(false);
	if (countDown != -1 && SDL_GetTicks() - countDown >= timeActivated * 1000) {
		tr->setPosition(Vector2D(pos.getX(), pos.getY() + speed));
	}
	Entity* p = mngr_->getPlayer();
	SDL_Rect r1 = p->getComponent<Transform>()->getRect(); SDL_Rect r2 = tr->getRect();
	if (SDL_HasIntersection(&r1, &r2)) {
		p->getComponent<Health>()->recieveDamage(ecs::Fire);
	}
}
