#include "PlayerAnimationComponent.h"

PlayerAnimationComponent::PlayerAnimationComponent()
{
}

PlayerAnimationComponent::~PlayerAnimationComponent()
{
}

void PlayerAnimationComponent::endAnim()
{
	currentAnimation = IDLE;
}
