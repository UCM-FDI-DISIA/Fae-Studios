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
	tr_->setPosition(tr_->getPosition() + Vector2D(1,0)); //Mueve la entidad sin necesidad de physics component
	if (SDL_HasIntersection(&player->getComponent<Transform>()->getRect(), &tr_->getRect())) { //Comprueba colisión con el jugador
		
		player->getComponent<Health>()->recieveDamage(ecs::Dark, true);
	}
	if (abs(initialXPos - tr_->getPosition().getX()) >= maxDistance) ent_->setAlive(false); //Recorre una distancia máxima antes de destruirse
}

FistComponent::~FistComponent()
{

}