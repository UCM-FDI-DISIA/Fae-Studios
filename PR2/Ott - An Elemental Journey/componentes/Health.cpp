#include "Health.h"
#include "../Src/Entity.h"

void Health::die()
{
    ent_->setAlive(false);
}

bool Health::recieveDamage(ecs::elements elem)
{
	//if() A�adir da�o dependiendo de la entidad
	actualLife -= elementsInfo::matrix[elem][elem];
	//startDamagedTime = SDL_GetTicks();
	if (actualLife <= 0) {
		die();
		return true;
	}
	else return false;
}
