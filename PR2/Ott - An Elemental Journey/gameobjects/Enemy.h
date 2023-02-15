#pragma once
#include "MovingObject.h"
#include "../utils/Elements.h"
#include <iostream>

// MOVER ARCHIVOS Y COLOCAR BIEN
// CLASE TEMPORAL PARA PROBAR COSAS

class Enemy : public MovingObject{
	enum triggerState {normal, preparing, attacking};
protected:
	int maxLives;
	int actualLives;
	elementsInfo::elements element;
	bool dead = false;

	uint PREPARING_TIME = 500;
	uint ATTACKING_TIME = 500;


	uint NEW_DIR = 1000;
	int startAttackingTime = 0;
	int startMovingTime = 0;
	int turningError = 1;
	double turningOffset = 0.75; // entre 0 y 1
	SDL_Rect attackTrigger;
	triggerState attackState;
	SDL_Rect detectingTrigger;
	bool detectPlayer;
	bool movee;  // TEMPORAL PARA PRUEBAS, BORRAR TODO LO RELACIONADO CON ESTO
	bool lookingRight = true;
	const int nearDistance = 50;
	bool grounded = false;

	GameObject* player;
public:
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, Vector2D dir = Vector2D(0,0), const Scale& scale = Scale(1.0f, 1.0f), float w = 110.0f, GameState* state = nullptr);
	virtual ~Enemy() = default;

	bool Damage(elementsInfo::elements e);

	void Die();

	void DetectPlayer();

	virtual void FollowPlayer();

	virtual void update();

	virtual void Move();

	int GetLives();

	bool isDead();

	virtual void Attack();

	void DetectAttackTrigger();

	//void playerCollide();

	void useGravity();
};


