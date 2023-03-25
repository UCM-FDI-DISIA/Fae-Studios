#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
class Acceleration : public Component
{
private:
	Entity* player;
	Transform* transform;
	Transform* playerTransform;
	PhysicsComponent* physics;
	bool waiting = false;
	Vector2D speed;
	bool start = false;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSS_PIVOT;
	Acceleration() {}
	~Acceleration() {}
	void initComponent() override;
	void update() override;
	inline void setWaiting(bool wait) { waiting = wait; speed = physics->getVelocity(); };
	inline bool getWaiting() { return waiting; };
};

