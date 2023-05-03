#include "../utils/checkML.h"
#include "ShieldComponent.h"
#include "../game/ecs.h"
#include "PlayerInput.h"
#include "ShieldAnimationComponent.h"

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

int ShieldComponent::elementalDamage(int dmg)
{
	auto inputComp = ent_->getComponent<PlayerInput>();
	switch (dmg)
	{
	case 0: 
		sdlutils().soundEffects().at("shield_block").play(0, ecs::_channel_PLAYER);
		ent_->getComponent<ShieldAnimationComponent>()->blockAttack();
		return -1;
	case 1: 
		sdlutils().soundEffects().at("shield_block").play(0, ecs::_channel_PLAYER);
		ent_->getComponent<ShieldAnimationComponent>()->blockAttack();
		return 0;
	case 2: {
		// guardShield(); 
		inputComp->stunStart(); 
		ent_->getComponent<ShieldAnimationComponent>()->breakShield();
		break; }
	default: break;
	}
	return -1;
}