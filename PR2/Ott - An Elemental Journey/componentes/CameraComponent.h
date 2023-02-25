#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "Transform.h"
#include "../Src/Entity.h"
class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent();
	virtual void initComponent();
	virtual void update();
	constexpr static cmpId_type id = ecs::_CAMERA;
private:
	Transform* playerTrnf_;
	Transform* tr_;
};

