#include "FireWallComponent.h"
#include "Health.h"
#include "FramedImage.h"
FireWallComponent::FireWallComponent(Vector2D d) : dir(d)
{
}


void FireWallComponent::initComponent()
{
	p = mngr_->getPlayer();
	player = p->getComponent<Transform>();
	tr_ = ent_->getComponent<Transform>();
	initialXPos = tr_->getPosition().getX();
	image = ent_->getComponent<FramedImage>();
}

void FireWallComponent::update()
{
	image->setCol(((SDL_GetTicks() / 150) % 8) + 2);
	tr_->setPosition(tr_->getPosition() + dir); //Mueve la entidad sin necesidad de physics component
	if (player->getPosition().getX() + player->getWidth() / 2 > tr_->getPosition().getX() && (player->getPosition().getX() + player->getWidth() / 2) < tr_->getPosition().getX() + tr_->getWidth()
		&& player->getPosition().getY() + player->getHeight() > tr_->getPosition().getY() && player->getPosition().getY() < tr_->getPosition().getY() + tr_->getHeight()) { //Comprueba colisión con el jugador

		mngr_->getPlayer()->getComponent<Health>()->recieveDamage(ecs::Fire, true);
	}
	if (abs(initialXPos - tr_->getPosition().getX()) >= maxDistance) ent_->setAlive(false); //Recorre una distancia máxima antes de destruirse
}

FireWallComponent::~FireWallComponent()
{
}