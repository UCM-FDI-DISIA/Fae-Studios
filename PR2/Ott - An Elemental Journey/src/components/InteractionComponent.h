#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
class InteractionComponent : public Component
{
public:
	InteractionComponent(void (*callback)(Manager* m));
	//Para las lámparas de teletransporte
	virtual ~InteractionComponent();
	void interact();


	constexpr static cmpId_type id = ecs::_INTERACTION;
private:
	
	void (*m_callback)(Manager* m);
};
