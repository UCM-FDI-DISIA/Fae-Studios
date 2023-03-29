//LIMPIO

#pragma once
#include "../ecs/Component.h"

class Generations : public Component
{
private:
	const static int maxGen = 3;
	int generations;
	int room;
public:
	constexpr static ecs::cmpId_type id = ecs::_GEN;
	Generations(int g, int room) : Component(), generations(g), room(room) {};
	inline int getGeneration() { return generations; }
	inline int getRoom() { return room; }
	static inline int getMaxGeneration() { return maxGen; }
	// el metodo que crea dos bichitos mas cuando se muere el grande, se llama desde el metodo die() de Health
	void Divide();
};