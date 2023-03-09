#include "../ecs/Component.h"
#include "EnemyAnimationController.h"
#include "../sdlutils/InputHandler.h"
#pragma once

class TestEnemyInput : public Component
{
public:
	TestEnemyInput() {};
	virtual ~TestEnemyInput() {};
	virtual void initComponent();
	virtual void update();
	constexpr static ecs::cmpId_type id = ecs::_CTRL;
private:
	EnemyAnimationComponent* anim_;
	float horizontalSpeed = 0;
	InputHandler* input_;

};

