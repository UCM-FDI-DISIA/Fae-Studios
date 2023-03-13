#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "EnemyAttack.h"

//brainstorm literal porque no se como hacerlo jeje
class EarthBossAttack : public Component
{
private:
	int waitingTime = 0;
	bool canAttack = true;
	bool attacking = false;
	Entity* player = nullptr;
	Transform* tr_ = nullptr;
	Transform* playerTr_ = nullptr;
	EnemyAttack* eAttack_ = nullptr;
	SDL_Rect BossZone_ = { 0, 0, 0, 0 };
	int X_Positions[5];
	SDL_Rect zones[5];

public:
	constexpr static ecs::cmpId_type id = ecs::_ATTACK;
	EarthBossAttack(SDL_Rect BossZone) : BossZone_(BossZone) {

		int aux = 0;
		for (int i = 0; i < 5; ++i) {
			zones[i].y = BossZone_.y; zones[i].x = BossZone_.x + aux;
			zones[i].w = BossZone_.w / 5; zones[i].h = BossZone_.h;

			X_Positions[i] = zones[i].x;

			aux += (BossZone_.x + BossZone_.w) / 5;
		}
	}

	void attack();
	void chooseRandomPos();
	void initComponent() override;
	void update() override;
	void setCanAttack(bool canAttack_) { canAttack = canAttack_; }
	bool getCanAttack() { return canAttack; }
};
