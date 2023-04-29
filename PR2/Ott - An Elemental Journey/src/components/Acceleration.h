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

	int state = 0;

public:
	constexpr static ecs::cmpId_type id = ecs::_BOSS_PIVOT;
	Acceleration():Component() {}
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

