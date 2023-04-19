#pragma once
#include "PhysicsComponent.h"
class PlatformMovementY : public Component{
private:
	PhysicsComponent* physics;
	float amplitude;
	float time;
public:
	PlatformMovementY(float a, float t) : Component(), physics(nullptr), amplitude(a), time(t) {};
	~PlatformMovementY() = default;
	void initComponent() override;
	void update() override;
};