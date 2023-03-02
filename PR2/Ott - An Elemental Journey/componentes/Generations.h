#pragma once
#include "Component.h"
class Generations : public Component
{
private:
	int generations;
public:
	constexpr static cmpId_type id = ecs::_GEN;
	Generations(int g) : Component(), generations(g) {};
	inline int getGeneration() { return generations; }
};

