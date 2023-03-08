#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"

class AddVine : public Component
{
public:
	bool haveVine;
	bool doesntHaveVine() { return haveVine; }
	void setVine() { haveVine = true; }
	AddVine(bool hV) : haveVine(hV) {};
	virtual ~AddVine() {};
	constexpr static cmpId_type id = ecs::_VINE;
};