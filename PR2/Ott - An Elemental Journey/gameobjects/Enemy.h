#pragma once
#include "MovingObject.h"
#include "../utils/Elements.h"
#include <iostream>

// MOVER ARCHIVOS Y COLOCAR BIEN
// CLASE TEMPORAL PARA PROBAR COSAS

class Enemy : public MovingObject{
	enum triggerState {normal, preparing, attacking};
private:
	int maxLives;
	int actualLives;
	elementsInfo::elements element;
	bool dead = false;

	const uint PREPARING_TIME = 500;
	const uint ATTACKING_TIME = 500;
	const uint NEW_DIR = 500;
	int startAttackingTime = 0;
	int startMovingTime = 0;
	SDL_Rect attackTrigger;
	triggerState attackState;
	SDL_Rect detectingTrigger;
	bool detectPlayer;
	bool movee;  // TEMPORAL PARA PRUEBAS, BORRAR TODO LO RELACIONADO CON ESTO
	bool lookingRight = true;
	const int nearDistance = 50;

	GameObject* player;
public:
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, Vector2D dir = Vector2D(0,0), const Scale& scale = Scale(1.0f, 1.0f), float w = 110.0f, GameState* state = nullptr);
	~Enemy();

	void Damage(elementsInfo::elements e);

	void Die();

	void DetectPlayer();

	void FollowPlayer();

	virtual void update();

	void Move();

	int GetLives();

	bool isDead();
};

