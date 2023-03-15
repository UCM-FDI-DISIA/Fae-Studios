#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "PlayerAnimationComponent.h"
#include "earthAnimationController.h"

class Health;
class Transform;
class PlayerAnimationComponent;
class PhysicsComponent;

// Ancho y Alto ataque de agua
const int WATER_ATACK_WIDTH =  300;
const int WATER_ATACK_HEIGHT =  50;

const int WATER_ATACK_TICK_TIME = 2000; // Cada cuantos ms tick de agua
const int WATER_ATACK_DURATION = 6000; // Duracion del ataque de agua en ms

const int EARTH_ATTACK_WIDTH = 300;
const int EARTH_ATTACK_HEIGHT = 50;

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
	bool attackEnemy(SDL_Rect& attackZone);
	void spawnFireball();
	void waterAttack(SDL_Rect &trigger);
	void deleteWaterAttack();

	// Variables
	Vector2D triggerPos;
	//Vector2D triggerWH;
	Vector2D watAtackTriggWH; // tamaño ataque de agua
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

	int waterDurationTimer; // timer duracion ataque de agua
	int waterTickTimer = 0; // timer tick de agua
	bool waterAttackActive;
	int earthDurationTimer;
	int earthTickTimer= 0;
	bool earthAttackActive;
	int colEarthtrigger;
	Entity* wAttack = nullptr; // Entidad ataque de agua
	Entity* tAttack = nullptr; // Entidad ataque de agua
};

