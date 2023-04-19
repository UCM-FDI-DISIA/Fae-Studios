#pragma once
#include "PhysicsComponent.h"
class PlatformMovementX : public Component {
private:
	PhysicsComponent* physics;
	float amplitude;
	float time, deltaTime;
public:
	constexpr static ecs::cmpId_type id = ecs::_PLATFORM_MOVEMENT;
	PlatformMovementX(float a, float t) : Component(), physics(nullptr), amplitude(a), time(t), deltaTime(SDL_GetTicks()) {};
	~PlatformMovementX() = default;
	void initComponent() override;
	void update() override;
};