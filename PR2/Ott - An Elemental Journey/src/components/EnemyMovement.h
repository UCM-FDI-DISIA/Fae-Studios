#pragma once
#include "Transform.h"
#include "PhysicsComponent.h"
#include "EnemyAttack.h"
#include "FramedImage.h"

class Health;

class EnemyMovement : public Component
{
private:
	PhysicsComponent* physics;
	Entity* player;
	Transform* transform;
	PhysicsComponent* playerCollider;
	Health* health_;
	FramedImage* image_;
	EnemyAttack* eAttack_;
	SDL_Rect trigger;

	bool playerDetected;
	bool canMove;
	int nearDistance;
	double turningOffset = 0.75; //A partir de aquí no entiendo, solo he ctrl c ctrl v
	int turningError = 3;
	float horizontalSpeed = 0.1;
	void MoveTriggers();
	bool collided = false;
	bool moving = false;
public:
	constexpr static ecs::cmpId_type id = ecs::_ENEMYMOV;
	EnemyMovement(float hSpeed, float wTrigger = 100.0f, float hTrigger = 100.0f) : Component() {
		player = nullptr;
		trigger.x = 0; trigger.y = 0;
		trigger.w = wTrigger; trigger.h = hTrigger;
		physics = nullptr;
		transform = nullptr;
		playerCollider = nullptr;
		playerDetected = false;
		canMove = true;
		horizontalSpeed = hSpeed;
	};
	void initComponent() override;
	void detectPlayer();
	void FollowPlayer();
	void ChangeDirection(bool ground, const SDL_Rect& result);
	inline void setCanMove(bool move) { canMove = move; }
	void update() override;
	bool isMoving() { return moving; };
};

