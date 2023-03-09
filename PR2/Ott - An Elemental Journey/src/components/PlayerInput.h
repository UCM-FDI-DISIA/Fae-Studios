#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include <iostream>
#include "Transform.h"
#include "PhysicsComponent.h"
#include "PlayerAnimationComponent.h"
#include "../ecs/Entity.h"

class PlayerInput : public Component
{
public:
	PlayerInput() : Component() {}
	virtual ~PlayerInput() = default;
	virtual void initComponent();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
private:
	Transform* tr_;
	PhysicsComponent* physics_;
	PlayerAnimationComponent* anim_;
	float horizontalSpeed = 0;
};

