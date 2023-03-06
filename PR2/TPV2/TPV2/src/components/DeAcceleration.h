#pragma once
#include "Transform.h"
class DeAcceleration : public Component
{
	const float deAccelerationFactor = 0.995f; //Factor que determina cuánto va a decelerar la nave en cada frame (tiene que ser <1)
	const float minVel = 0.05f; //Valor mínimo que puede alcanzar la velocidad hasta que se detenga
private:
	Transform* transform = nullptr;
public:
	constexpr static ecs::cmpId_type id = ecs::_DEACC;
	DeAcceleration() : Component() {
		transform = nullptr;
	};
	virtual ~DeAcceleration() = default;
	void initComponent() override;
	void update() override;
};

