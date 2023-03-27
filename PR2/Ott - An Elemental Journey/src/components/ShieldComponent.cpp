#include "../utils/checkML.h"
#include "ShieldComponent.h"
#include "../game/ecs.h"

void ShieldComponent::initComponent() {
	image_ = ent_->getComponent<FramedImageOtt>();
	health_ = ent_->getComponent<Health>();
	physics_ = ent_->getComponent<PhysicsComponent>();
}

void ShieldComponent::takeShield() {
	image_->shielded(true);
	physics_->slowed();
	hasTakenShieldOut = true;
}

void ShieldComponent::guardShield() {
	image_->shielded(false);
	hasTakenShieldOut = false;
}