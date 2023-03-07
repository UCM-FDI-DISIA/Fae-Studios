#include "Bullet.h"
#include "../Src/Entity.h"
#include "../Src/Manager.h"

void Bullet::initComponent()
{
	player = mngr_->getPlayer();
	physics = ent_->getComponent<PhysicsComponent>();
}
