#include "Follow.h"
#include "../ecs/Entity.h"
void Follow::initComponent()
{
	transform = ent_->getComponent<Transform>();
	player = mngr_->getEntities(ecs::_grp_GENERAL)[0];
	playerTransform = player->getComponent<Transform>();
}

void Follow::update()
{
	transform->setVelocity(transform->getVelocity().rotate(transform->getVelocity().angle(playerTransform->getPosition() - transform->getPosition()) > 0 ? 1.0f : -1.0f)); //Su vector de velocidad se calcula en cada frame dependiendo de la posici�n del jugador
}
