#pragma once
#include "PhysicsComponent.h"
class PlatformMovementX : public Component {
private:
	PhysicsComponent* physics;
	float amplitude;
	float time;
public:
	PlatformMovementX(float a, float t) : Component(), physics(nullptr), amplitude(a), time(t) {};
	~PlatformMovementX() = default;
	void initComponent() override;
	void update() override;
};