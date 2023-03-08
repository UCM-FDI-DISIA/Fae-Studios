#pragma once
#include "EnemyAttack.h"
#include "Health.h"
class SlimeAttack : public Component
{
private:
	EnemyAttack* attack;
	PhysicsComponent* physics;
	Transform* transform;
	Health* health;
	SDL_Rect damageZone;
	void layDownAdjust();
	void getUpAdjust();
	void divide();
public:
	constexpr static cmpId_type id = ecs::_ATTACK;
	SlimeAttack() : Component() {
		attack = nullptr;
		physics = nullptr;
		transform = nullptr;
		health = nullptr;
		damageZone = { 0, 0, 0, 0 };
	}
	void initComponent() override;
	void update() override;
};

