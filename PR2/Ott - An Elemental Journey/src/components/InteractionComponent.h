#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <functional>


class InteractionComponent : public Component
{
public:
	InteractionComponent(std::function<void()> const& callback) : callback(callback) {}
	//Para las lámparas de teletransporte
	virtual ~InteractionComponent() = default;
	void interact() { callback(); }


	constexpr static ecs::cmpId_type id = ecs::_INTERACTION;
private:
	
	//void (*m_callback)();
	std::function<void()> callback;
};
