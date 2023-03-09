#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"
#include "../Src/Entity.h"

class AddVine : public Component
{
private:
	Entity* myVine = nullptr;
	Vector2D finalPos;
public:
	bool haveVine;
	bool doesntHaveVine() { return haveVine; }
	void setVine() { haveVine = true; }
	AddVine(bool hV, Entity* vine, Vector2D finPos) : haveVine(hV), myVine(vine), finalPos(finPos) {};
	virtual ~AddVine() {};
	constexpr static cmpId_type id = ecs::_VINE;
	Entity* getVine() { return myVine; }
	Vector2D getPosFin() { return finalPos;}
};