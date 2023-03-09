#include "Component.h"
#include "EnemyAnimationController.h"
#include "../utils/InputHandler.h"
#pragma once
class TestEnemyInput : public Component
{
public:
	TestEnemyInput() {};
	virtual ~TestEnemyInput() {};
	virtual void initComponent();
	virtual void update();
	constexpr static cmpId_type id = ecs::_TESTENEMYINPUT;
private:
	EnemyAnimationComponent* anim_;
	float horizontalSpeed = 0;
	InputHandler* input_;

};

