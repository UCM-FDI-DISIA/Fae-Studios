#pragma once
#include "EnemyAttack.h"
#include "Generations.h"
class SlimeStates : public Component
{
private:
	bool ajusta; //booleano para que una cosa solo se haga una vez en el update
	Generations* actGen;
	Entity* player;
	EnemyAttack* attack;
	PhysicsComponent* physics;
	Transform* transform;
	SDL_Rect damageZone;
	void layDownAdjust();
	void getUpAdjust();

public:
	constexpr static ecs::cmpId_type id = ecs::_ENEMYSTATES;
	SlimeStates() : Component() {
		ajusta = true;
		player = nullptr;
		attack = nullptr;
		damageZone = { 0,0,0,0 };
		physics = nullptr;
		transform = nullptr;
		actGen = nullptr;
	}
	void initComponent() override;
	void update() override;
};

