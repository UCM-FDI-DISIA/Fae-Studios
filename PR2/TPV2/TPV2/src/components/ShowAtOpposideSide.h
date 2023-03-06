#pragma once
#include "Transform.h"
#include"../sdlutils/SDLUtils.h"
class ShowAtOpposideSide : public Component
{
private:
	Transform* transform;
public:
	constexpr static ecs::cmpId_type id = ecs::_OPPOSIDESIDE;
	ShowAtOpposideSide() : Component() {
		transform = nullptr;
	}
	virtual ~ShowAtOpposideSide() = default;
	void initComponent() override;
	void update() override;
};

