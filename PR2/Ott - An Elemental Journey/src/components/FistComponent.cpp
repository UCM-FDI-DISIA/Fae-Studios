#include "FistComponent.h"
#include "Health.h"


void FistComponent::initComponent()
{
	player = mngr_->getPlayer()->getComponent<Transform>();
	tr_ = ent_->getComponent<Transform>();
	initialXPos = tr_->getPosition().getX();
	initialYPos = tr_->getPosition().getY();
}

void FistComponent::update()
{
	tr_->setPosition(tr_->getPosition() + dir); //Mueve la entidad sin necesidad de physics component
	
	if (player->getPosition().getX()+player->getWidth()/2>tr_->getPosition().getX() && (player->getPosition().getX() + player->getWidth() / 2)< tr_->getPosition().getX() + tr_->getWidth()
		&& player->getPosition().getY()+player->getHeight()>tr_->getPosition().getY() && player->getPosition().getY()< tr_->getPosition().getY() + tr_->getHeight()) { //Comprueba colisión con el jugador
		
		mngr_->getPlayer()->getComponent<Health>()->recieveDamage(ecs::Dark, true);
	}
	if (abs(initialXPos - tr_->getPosition().getX()) >= maxDistance || abs(initialYPos - tr_->getPosition().getY()) >= maxDistance) ent_->setAlive(false); //Recorre una distancia máxima antes de destruirse
}