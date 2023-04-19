#include "FistComponent.h"
#include "Health.h"


void FistComponent::initComponent()
{
	player = mngr_->getPlayer();
	tr_ = ent_->getComponent<Transform>();
	initialXPos = tr_->getPosition().getX();
}

void FistComponent::update()
{
	tr_->setPosition(tr_->getPosition() + dir); //Mueve la entidad sin necesidad de physics component
	if (SDL_HasIntersection(&player->getComponent<Transform>()->getRect(), &tr_->getRect())) { //Comprueba colisi�n con el jugador
		player->getComponent<Health>()->recieveDamage(ecs::Fire, true);
	}
	if (abs(initialXPos - tr_->getPosition().getX()) >= maxDistance) ent_->setAlive(false); //Recorre una distancia m�xima antes de destruirse
}

FistComponent::~FistComponent()
{

}