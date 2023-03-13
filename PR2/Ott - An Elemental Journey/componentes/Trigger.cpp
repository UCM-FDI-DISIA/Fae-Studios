#include "Trigger.h"
Trigger::Trigger() {
}
void Trigger::update() {
	if (mngr_->getHandler(ecs::PLAYER) != nullptr) {
		player_ = mngr_->getHandler(ecs::PLAYER);
		auto interactionIt = mngr_->getEntitiesByGroup(ecs::_grp_TRIGGER).begin();
		while (interactionIt != mngr_->getEntitiesByGroup(ecs::_grp_TRIGGER).end()) {
			Entity* ents = *interactionIt;
		
				SDL_Rect r1 = player_->getComponent<Transform>()->getRect();
				SDL_Rect r2 = tr_->getRect();
				if (SDL_HasIntersection(&r1, &r2)) {
					if (ents->hasComponent<EnterBossRoom>()) {
						ents->getComponent<EnterBossRoom>()->enterRoom();
						ents->getComponent<EnterBossRoom>()->startAnim();
					}
				}
		
			interactionIt++;
		}

	}
}

void Trigger::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	
}