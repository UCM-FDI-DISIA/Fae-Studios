#pragma once
#include "../ecs/Component.h"

class Generations : public Component
{
private:
	int generations;
public:
	constexpr static ecs::cmpId_type id = ecs::_GEN;
	Generations(int g) : Component(), generations(g) {};
	inline int getGeneration() { return generations; }
};

