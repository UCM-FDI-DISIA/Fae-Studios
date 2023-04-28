#include "Trigger.h"
#include "LoreRoom.h"
#include "Health.h"
Trigger::Trigger() {
}
void Trigger::update() {
	if (!detected && mngr_->getPlayer() != nullptr) {
		player_ = mngr_->getPlayer();
	
		SDL_Rect r1 = player_->getComponent<Transform>()->getRect();
		SDL_Rect r2 = tr_->getRect();
		if (SDL_HasIntersection(&r1, &r2)) {
			if (ent_->hasComponent<EnterBossRoom>()) {
				ent_->getComponent<EnterBossRoom>()->enterRoom();
				detected = true;
			}
			else if (ent_->hasComponent<LoreRoom>()) {
				ent_->getComponent<LoreRoom>()->startLore();
				detected = true;
			}
		}
	}
	if (player_->getComponent<Health>()->getHealth() <= 0) detected = false;
}

void Trigger::initComponent()
{
	tr_ = ent_->getComponent<Transform>();

}