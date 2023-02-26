#pragma once
#include "Component.h"
#include "../utils/InputHandler.h"
#include <iostream>
#include "Transform.h"
#include "PhysicsComponent.h"
#include "PlayerAnimationComponent.h"
#include "../Src/Entity.h"
using namespace std;
class PlayerInput : public Component
{
public:
	PlayerInput();
	virtual ~PlayerInput();
	virtual void initComponent();
	virtual void update();
	constexpr static cmpId_type id = ecs::_CTRL;
private:
	Transform* tr_;
	PhysicsComponent* physics_;
	PlayerAnimationComponent* anim_;
};

