#include "FirePillarComponent.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"
#include "FramedImage.h"
bool FirePillarComponent::collidesPlayer()
{
	Entity* p = mngr_->getPlayer();
	auto player = p->getComponent<Transform>();
	auto tr = ent_->getComponent<Transform>();
	return (player->getPosition().getX() > tr->getPosition().getX() && (player->getPosition().getX() + player->getWidth() / 2) < tr->getPosition().getX() + tr->getWidth() && player->getPosition().getY() + player->getHeight() > tr->getPosition().getY() && player->getPosition().getY() < tr->getPosition().getY() + tr->getHeight());
}
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
	if (countDown != -1 && collidesPlayer()) {
		bool dir = true;
		if(r1.x < r2.x) dir = false;
		p->getComponent<Health>()->recieveDamage(ecs::Fire,dir);
	}
	std::cout << ent_->getComponent<FramedImage>()->getCurrentCol() << std::endl;
	int c = ent_->getComponent<FramedImage>()->getCurrentCol();
	c++;
	ent_->getComponent<FramedImage>()->setCol((SDL_GetTicks()/100)&5);
}
