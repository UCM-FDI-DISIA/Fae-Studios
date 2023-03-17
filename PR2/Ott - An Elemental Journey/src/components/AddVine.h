//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"

class AddVine : public Component {
private:
	Entity* myVine;
	bool haveVine;
	Vector2D finalPos;

public:
	constexpr static ecs::cmpId_type id = ecs::_VINE;

	AddVine(bool hV, Entity* vine, Vector2D finPos) : Component(), haveVine(hV), myVine(vine), finalPos(finPos) {};

	inline bool doesntHaveVine() { return haveVine; }
	inline void setVine() { haveVine = true; }
	inline Entity* getVine() { return myVine; }
	inline Vector2D getPosFin() { return finalPos; }
};