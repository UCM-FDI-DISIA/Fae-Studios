#pragma once
#include "Component.h"
class Generations : public Component
{
private:
	const static int maxGen = 3;
	int generations;
public:
	constexpr static cmpId_type id = ecs::_GEN;
	Generations(int g) : Component(), generations(g) {};
	inline int getGeneration() { return generations; }
	static inline int getMaxGeneration() { return maxGen; }
	// el metodo que crea dos bichitos mas cuando se muere el grande, se llama desde el metodo die() de Health
	void Divide();
};

