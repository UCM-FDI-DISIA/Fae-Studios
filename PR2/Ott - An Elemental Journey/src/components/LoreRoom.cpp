#include "LoreRoom.h"
#include "PhysicsComponent.h"
#include "LoreTextAnims.h"
void LoreRoom::startLore() {
	if(mngr_->getPlayer() != nullptr)
		mngr_->getPlayer()->getComponent<PhysicsComponent>()->Stop();
	text->getComponent<LoreTextAnims>()->startAnim();
}
