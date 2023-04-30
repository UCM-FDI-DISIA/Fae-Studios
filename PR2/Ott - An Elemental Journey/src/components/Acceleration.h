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
	const int distanceFactor = 750;
	const int minDistance = distanceFactor * 2 / 3;
	const float distanceSpeed = 1.5;

	int state = 0;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSS_PIVOT;
	Acceleration() {}
	~Acceleration() {}
	void initComponent() override;
	void update() override;
	inline void setWaiting(bool wait, int num) { waiting = wait; speed = physics->getVelocity(); state = num; };
	inline bool getWaiting() { return waiting; };
	inline void restart() {
		waiting = false;
		physics->setVelocity(speed);
	};
};

