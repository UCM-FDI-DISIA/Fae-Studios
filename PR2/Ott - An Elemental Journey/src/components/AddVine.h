#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"

class AddVine : public Component
{
public:
	constexpr static ecs::cmpId_type id = ecs::_VINE;
	bool haveVine;
	bool doesntHaveVine() { return haveVine; }
	void setVine() { haveVine = true; }
	AddVine(bool hV) : haveVine(hV) {};
	virtual ~AddVine() {};
};