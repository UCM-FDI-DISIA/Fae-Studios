#include "AutoDestroy.h"
#include "../ecs/Entity.h"
AutoDestroy::~AutoDestroy()
{
}
void AutoDestroy::update()
{
	if (SDL_GetTicks() - startCountDown >= time*1000) {
		ent_->setAlive(false);
	}
}
