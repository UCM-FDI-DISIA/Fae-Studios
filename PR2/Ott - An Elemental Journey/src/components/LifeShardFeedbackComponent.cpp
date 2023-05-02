#include "LifeShardFeedbackComponent.h"

void LifeShardFeedbackComponent::update() {
	
	Vector2D pos = text_->getPosition() + Vector2D(0, -0.001f);
	text_->setPosition(pos);

	if ((originalPos_ - text_->getPosition()).getY() >= 260.0f) {
		ent_->setAlive(false);
	}
}

void LifeShardFeedbackComponent::initComponent() {
	text_ = ent_->getComponent<TextComponent>();
	originalPos_ = text_->getPosition();
}