#include "FireWallComponent.h"
#include "Health.h"
FireWallComponent::FireWallComponent(Vector2D d) : dir(d)
{
}


void FireWallComponent::initComponent()
{
	player = mngr_->getPlayer();
	tr_ = ent_->getComponent<Transform>();
	initialXPos = tr_->getPosition().getX();
}

void FireWallComponent::update()
{
	tr_->setPosition(tr_->getPosition() + dir); //Mueve la entidad sin necesidad de physics component
	if (SDL_HasIntersection(&player->getComponent<Transform>()->getRect(), &tr_->getRect())) { //Comprueba colisión con el jugador
		player->getComponent<Health>()->recieveDamage(ecs::Fire, true);
	}
	if (abs(initialXPos - tr_->getPosition().getX()) >= maxDistance) ent_->setAlive(false); //Recorre una distancia máxima antes de destruirse
}

FireWallComponent::~FireWallComponent()
{
}