#pragma once
#include "../ecs/Component.h"
#include "Transform.h"
#include "EnemyAttack.h"
#include "GrowVine.h"
#include <vector>

//brainstorm literal porque no se como hacerlo jeje
class EarthBossAttack : public Component
{
private:
	/*int waitingTime = 0;
	bool canAttackFall = false;
	bool attackingFall = false;
	bool canAttackVine = true;
	bool attackingVine = false;*/
	Entity* player = nullptr;
	Transform* tr_ = nullptr;
	Transform* playerTr_ = nullptr;
	//EnemyAttack* eAttack_ = nullptr;
	SDL_Rect BossZone_ = { 0, 0, 0, 0 };
	SDL_Rect zones[5];
	//std::vector<Entity*> vines;

public:
	constexpr static ecs::cmpId_type id = ecs::_ATTACK;
	EarthBossAttack(SDL_Rect BossZone/*, std::vector<Entity*> vines_*/) : BossZone_(BossZone) {
		/*for (int j = 0; j < vines_.size(); ++j) {
			vines[j] = vines_[j];
		}
		int aux = 0;
		for (int i = 0; i < 5; ++i) {
			zones[i].y = BossZone_.y; zones[i].x = BossZone_.x + aux;
			zones[i].w = BossZone_.w / 5; zones[i].h = BossZone_.h;
			aux += (BossZone_.x + BossZone_.w) / 5;
		}*/
	}

	void attack();
	/*void chooseRandomPos();*/
	void initComponent() override;
	void update() override;
	/*void setCanAttackVine(bool canAttack_) { canAttackVine = canAttack_; }
	bool getCanAttackVine() { return canAttackVine; }
	void setCanAttackFall(bool canAttack_) { canAttackFall = canAttack_; }
	bool getCanAttackFall() { return canAttackFall; }*/
};
