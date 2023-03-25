#pragma once
#include "PlayerInput.h"
class ElementObject : public Component
{
private:
	ecs::elements elem;
public:
	constexpr static ecs::cmpId_type id = ecs::_GET_ELEMENT;
	ElementObject(ecs::elements e) : Component(), elem(e) {};
	inline ecs::elements getElement() { return elem; }
};

