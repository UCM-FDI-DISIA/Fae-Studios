#pragma once
#include "../ecs/Component.h"
#include "TextComponent.h"

const int GO_UP_TIME = 500;

class LifeShardFeedbackComponent : public Component {
private:
	TextComponent* text_;

	Vector2D originalPos_;

public:
	constexpr static ecs::cmpId_type id = ecs::_LIFE_SHARD_FEEDBACK;

	LifeShardFeedbackComponent() : Component(), text_(nullptr) {}

	void initComponent() override;
	void update() override;
};

