#pragma once
#include "../ecs/Component.h"
class Generations : public Component 
{
private:
	int generation; //Componente que s�lo guarda la generaci�n del asteroide
public:
	constexpr static ecs::cmpId_type id = ecs::_GEN;
	Generations(int g) : Component(), generation(g) {};
	virtual ~Generations() = default;
	inline int getGeneration() const { return generation; }
	inline void setGeneration(int g) { generation = g; }
};

