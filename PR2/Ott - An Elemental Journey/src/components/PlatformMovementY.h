#pragma once
#include "PhysicsComponent.h"
#include "Transform.h"
class PlatformMovementY : public Component{
private:
	PhysicsComponent* physics;
	Transform* transform;
	float min, max, roomScale;
public:
	constexpr static ecs::cmpId_type id = ecs::_PLATFORM_MOVEMENT;
	PlatformMovementY(float min_, float max_, float r) : Component(), physics(nullptr), transform(nullptr), min(min_), max(max_), roomScale(r) {};
	~PlatformMovementY() = default;
	void initComponent() override;
	void update() override;
};