#include "LoreRoom.h"
#include "PhysicsComponent.h"
void LoreRoom::startLore() {
	player_->getComponent<PhysicsComponent>()->Stop();
}