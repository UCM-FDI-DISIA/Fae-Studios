//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "Transform.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"


class CameraComponent : public Component {
private:
	Transform* playerTrnf_;
	Transform* tr_;

public:
	constexpr static ecs::cmpId_type id = ecs::_CAMERA;
	SDL_Rect camera;

	CameraComponent() : Component(), playerTrnf_(nullptr), tr_(nullptr), camera({0,0,0,0}) {}
	
	virtual void initComponent();
	virtual void update();
};

