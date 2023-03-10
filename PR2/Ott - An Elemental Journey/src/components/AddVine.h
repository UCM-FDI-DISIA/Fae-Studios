//LIMPIO

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../ecs/Entity.h"

class AddVine : public Component {
private:
	bool haveVine;

public:
	constexpr static ecs::cmpId_type id = ecs::_VINE;

	AddVine(bool hV) : Component(), haveVine(hV) {};
	virtual ~AddVine() = default;

	inline bool doesntHaveVine() { return haveVine; }
	inline void setVine() { haveVine = true; }
};