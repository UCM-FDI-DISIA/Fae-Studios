#pragma once
#include "Component.h"
#include "../dependencies/Vector2D.h"

class Health;
class Transform;
class PlayerAnimationComponent;
class PhysicsComponent;


class PlayerAttack : public Component
{
public:
	PlayerAttack(int width = 100, int height = 100);
	virtual ~PlayerAttack() {};
	virtual void initComponent();
	virtual void update();
	void startAttack();
	constexpr static cmpId_type id = ecs::_PLAYERATTACK;
private:
	void MoveTrigger();
	Vector2D triggerPos;
	Vector2D triggerWH;
	Transform* tr_;
	Health* health_;
	PlayerAnimationComponent* anim_;
	PhysicsComponent* physics;
	bool canAttack;
	int startAttackingTime;
	const int AttackTime = 200;
};

