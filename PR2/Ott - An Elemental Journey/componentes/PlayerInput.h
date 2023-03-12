#pragma once
#include "Component.h"
#include "../utils/InputHandler.h"
#include <iostream>
#include "Transform.h"
#include "PhysicsComponent.h"
#include "PlayerAnimationComponent.h"
#include "PlayerAttack.h"
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
	void setActive(bool b) {
		active = b;
	}
private:
	Transform* tr_;
	PhysicsComponent* physics_;
	PlayerAnimationComponent* anim_;
	PlayerAttack* attack_;
	float horizontalSpeed = 0;
	bool active = true;
};

