#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "PlayerAnimationComponent.h"

class Health;
class Transform;
class PlayerAnimationComponent;
class PhysicsComponent;

// Ancho y Alto ataque de agua
const int WATER_ATACK_WIDTH =  300;
const int WATER_ATACK_HEIGHT =  50;

const int WATER_ATACK_TICK_TIME = 2000; // Cada cuantos ms tick de agua
const int WATER_ATACK_DURATION = 6000; // Duracion del ataque de agua en ms

class PlayerAttack : public Component
{
public:
	PlayerAttack(int width = 100, int height = 100);
	virtual ~PlayerAttack() {};
	virtual void initComponent();
	virtual void update();
	void startAttack();
	constexpr static ecs::cmpId_type id = ecs::_PLAYERATTACK;
private:
	// Metodos
	void MoveTrigger(Vector2D attackWH);
	void attackEnemy(SDL_Rect& attackZone);

	// Variables
	Vector2D triggerPos;
	Vector2D triggerWH;
	Vector2D watAtackTriggWH; // tamaño ataque de agua
	Transform* tr_;
	Health* health_;
	PlayerAnimationComponent* anim_;
	PhysicsComponent* physics;
	bool canAttack;
	int startAttackingTime;
	const int AttackTime = 200;

	int waterDurationTimer; // timer duracion ataque de agua
	int waterTickTimer = 0; // timer tick de agua
	bool waterAttackActive;
	Entity* wAttack = nullptr; // Entidad ataque de agua
};

