#pragma once
#include "Component.h"
class InteractionComponent : public Component
{
public:
	InteractionComponent(void (*callback)());
	//InteractionComponent(void (*callback)(Manager* e));
	virtual ~InteractionComponent();
	void interact();
	//void interact(Manager* e);

	constexpr static cmpId_type id = ecs::_INTERACTION;
private:
	void (*m_callback)();
	//void (*m_callback_manager)(Manager* g);
};

