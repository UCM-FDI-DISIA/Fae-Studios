#include "Health.h"
#include "../Src/Entity.h"

void Health::die()
{
    ent_->setAlive(false);
}

bool Health::recieveDamage(ecs::elements elem)
{
	actualLife -= elementsInfo::matrix[elem][elem];
	//startDamagedTime = SDL_GetTicks();
	if (actualLife <= 0) {
		die();
		return true;
	}
	else return false;
}
