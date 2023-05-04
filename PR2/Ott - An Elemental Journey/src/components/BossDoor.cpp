#include "BossDoor.h"
#include "../sdlutils/InputHandler.h"
#include "PlayerInput.h"

void BossDoor::initComponent() {
	
	image = ent_->getComponent<Image>();
}
void BossDoor::unlockElem(ecs::elements elem)
{
	if (elem == ecs::Earth)
	{
		image->changeText(&sdlutils().images().at("BossDoor_Earth"));
	}
	else if (elem == ecs::Water)
	{
		image->changeText(&sdlutils().images().at("BossDoor_Water"));
	}
	else if (elem == ecs::Fire)
	{
		image->changeText(&sdlutils().images().at("BossDoor_Fire"));
		open = true;
	}
}
