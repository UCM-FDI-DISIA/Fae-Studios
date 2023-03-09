#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class InteractionComponent : public Component
{
public:
	InteractionComponent(void (*callback)(Manager* m)) : m_callback(callback) {}
	//Para las lámparas de teletransporte
	virtual ~InteractionComponent() = default;
	void interact() { m_callback(mngr_); }


	constexpr static ecs::cmpId_type id = ecs::_INTERACTION;
private:
	
	void (*m_callback)(Manager* m);
};
