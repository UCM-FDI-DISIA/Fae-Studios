#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"


class CameraComponent : public Component
{
public:
	CameraComponent() : Component() {}
	virtual ~CameraComponent() = default;
	virtual void initComponent();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_CAMERA;
	SDL_Rect camera;
private:
	Transform* playerTrnf_;
	Transform* tr_;
};

