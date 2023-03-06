#pragma once
#include"../sdlutils/SDLUtils.h"
#include "Transform.h"
class DisableOnExit : public Component
{
private:
	Transform* transform;
public:
	constexpr static ecs::cmpId_type id = ecs::_OPPOSIDESIDE;
	DisableOnExit() : Component(){
		transform = nullptr;
	}
	virtual ~DisableOnExit() = default;
	void initComponent() override;
	void update() override;
};

