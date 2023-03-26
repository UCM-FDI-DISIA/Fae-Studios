#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "PlayerAnimationComponent.h"
#include "earthAnimationController.h"
#include "WaterAnimationController.h"

class Health;
class Transform;
class PlayerAnimationComponent;
class PhysicsComponent;

// Ancho y Alto ataque de agua
const int WATER_ATTACK_WIDTH =  300;
const int WATER_ATTACK_HEIGHT =  50;

const int WATER_ATTACK_TICK_TIME = 2000; // Cada cuantos ms tick de agua
const int WATER_ATTACK_DURATION = 6000; // Duracion del ataque de agua en ms

const int EARTH_ATTACK_WIDTH = 300;
const int EARTH_ATTACK_HEIGHT = 50;

const int FIRE_ATTACK_WIDTH = 100;
const int FIRE_ATTACK_HEIGHT = 100;

class PlayerAttack : public Component
{
public:
	PlayerAttack(int width = 100, int height = 100);
	virtual ~PlayerAttack() {};
	virtual void initComponent();
	virtual void update();
	inline void deleteEarthAttack()
	{
		earthAttackActive = false;
		tAttack->setAlive(false);

		if (chargedAttack)
			tAttack2->setAlive(false);
	}

	inline void deleteWaterAttack()
	{
		waterAttackActive = false;
		wAttack->setAlive(false);
	}

	inline void startAttack(bool charged) {
		startAttackingTime = SDL_GetTicks();
		canAttack = true;
		chargedAttack = charged;
	}
	constexpr static ecs::cmpId_type id = ecs::_PLAYERATTACK;
private:
	// Metodos
	void MoveTrigger(Vector2D attackWH);
	void MoveChargedEarthTrigger(Vector2D attackWH2);
	bool attackEnemy(SDL_Rect& attackZone);
	void spawnFireball();
	void moveAttack(Transform* tr);
	void moveChargedEarthAttack(Transform* tr, Transform* tr2);
	void waterChargedAttack(SDL_Rect &trigger);

	// Variables
	//Vector2D triggerWH;
	Vector2D watAtackTriggWH; // tama�o ataque de agua
	Transform* tr_;
	Health* health_;
	PlayerAnimationComponent* anim_;
	PhysicsComponent* physics;
	bool canAttack, chargedAttack;
	int startAttackingTime, lastFireBallTime, timeBetweenFireBalls = 250, remainingAttacks = 0;
	const int AttackTime = 200;
	int triggerWidth;
	int triggerHeight;
	SDL_Rect trigger;
	SDL_Rect trigger2;

	bool chargedLight = false;
	int waterDurationTimer; // timer duracion ataque de agua
	int waterTickTimer = 0; // timer tick de agua
	bool waterAttackActive;
	int earthDurationTimer;
	int earthTickTimer= 0;
	bool earthAttackActive;
	int colTrigger;
	Entity* wAttack = nullptr; // Entidad ataque de agua
	Entity* tAttack = nullptr; // Entidad ataque de tierra
	Entity* tAttack2 = nullptr; // Entidad ataque tierra cargado
};

