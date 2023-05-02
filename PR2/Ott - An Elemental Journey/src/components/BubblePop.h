#pragma once
#include "../ecs/Component.h"

class BubblePop: public Component
{

private:
	
public:
	constexpr static ecs::cmpId_type id = ecs::_BUBBLE_POP;

	BubblePop() :Component(){};

	void initComponent() override;
	void update() override;
};

