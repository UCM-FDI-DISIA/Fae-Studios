#pragma once
#include "Transform.h"
#include "PhysicsComponent.h"

class EnemyMovement : public Component
{
private:
	PhysicsComponent* physics;
	Entity* player;
	Transform* transform;
	Transform* playerTransform;
	SDL_Rect trigger;

	bool playerDetected;
	bool canMove;
	int nearDistance;
	double turningOffset = 0.75; //A partir de aquí no entiendo, solo he ctrl c ctrl v
	int turningError = 1;
	float horizontalSpeed = 1;
	void MoveTriggers();
	bool collided = false;
public:
	constexpr static ecs::cmpId_type id = ecs::_ENEMYMOV;
	EnemyMovement(float wTrigger = 100.0f, float hTrigger = 100.0f) : Component() {
		player = nullptr;
		trigger.x = 0; trigger.y = 0;
		trigger.w = wTrigger; trigger.h = hTrigger;
		physics = nullptr;
		transform = nullptr;
		playerTransform = nullptr;
		playerDetected = false;
		canMove = true;
	};
	void initComponent() override;
	void detectPlayer();
	void FollowPlayer();
	void ChangeDirection(bool ground, const SDL_Rect& result);
	inline void setCanMove(bool move) { canMove = move; }
	void update() override;
};

