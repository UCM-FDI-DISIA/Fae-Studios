#pragma once
#include "PhysicsComponent.h"
class PlatformMovementY : public Component{
private:
	PhysicsComponent* physics;
	float amplitude;
	float time, deltaTime;
public:
	constexpr static ecs::cmpId_type id = ecs::_PLATFORM_MOVEMENT;
	PlatformMovementY(float a, float t) : Component(), physics(nullptr), amplitude(a), time(t), deltaTime(SDL_GetTicks()) {};
	~PlatformMovementY() = default;
	void initComponent() override;
	void update() override;
};