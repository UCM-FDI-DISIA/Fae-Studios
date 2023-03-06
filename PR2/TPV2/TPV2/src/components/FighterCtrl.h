#pragma once
#include "Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SoundEffect.h"

class FighterCtrl : public Component
{
	const float MAX_VEL = 3.0f;
private:
	Transform* transform;
public:
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
	FighterCtrl() : Component() {
		transform = nullptr;
	};
	virtual ~FighterCtrl() = default;
	void initComponent() override;
	void handleInput() override;
};

