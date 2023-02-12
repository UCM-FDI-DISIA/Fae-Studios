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
	const uint NEW_DIR = 5000;
	int startAttackingTime = 0;
	int startMovingTime = 0;
	SDL_Rect attackTrigger;
	triggerState attackState;
	SDL_Rect detectingTrigger;
	bool detectPlayer;

	GameObject* player;
public:
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, Vector2D dir = Vector2D(0,0), const Scale& scale = Scale(1.0f, 1.0f), float w = 1.0f, float h = 1.0f): MovingObject(position, texture, dir, scale), actualLives(lives), element(elem), player(p) {
		maxLives = lives * 2;  // Representación interna doblada
		actualLives = lives * 2;
		speed = 0.1;

		attackTrigger.x = position.getX() - w; attackTrigger.y = position.getY();
		attackTrigger.w = w; attackTrigger.h = h;
		attackState = normal;

		detectingTrigger.x = position.getX() - 2 * w; detectingTrigger.y = position.getY();
		detectingTrigger.w = 2 * w; detectingTrigger.h = h;
		detectPlayer = false;
	}
	~Enemy() {

	}

	void Damage(elementsInfo::elements e) {
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) Die();
	}

	void Die() {
		dead = true;
		std::cout << "Muerto" << endl;
		// borrar o marcar booleano para borrar después
	}

	void OnEnterAttack() {
		if (attackState == normal) {
			attackState = preparing;
		}
		else if (attackState == attacking) {
			//Player.Damage(element) supongo
		}
	}

	void OnEnterDetection() {
		dir = (player->getRect().x - dir.getX(), dir.getY());
		dir.normalize();
		detectPlayer = true;
	}

	virtual void update() { //Falta el movimiento del enemigo
		int frameTime =  SDL_GetTicks() - startAttackingTime;
		int frameMovingTime = SDL_GetTicks() - startMovingTime;
		if (attackState == preparing && frameTime >= PREPARING_TIME) {
			attackState = attacking;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == attacking && frameTime >= ATTACKING_TIME) {
			attackState = normal;
			startAttackingTime = SDL_GetTicks();
		}

		if (dir.getX() > 0)
			attackTrigger.x = position.getX() + width;
		else
			attackTrigger.x = position.getX() - attackTrigger.w;

		attackTrigger.y = position.getY();

		if (!detectPlayer && frameMovingTime >= NEW_DIR) {
			dir = { rand() % 3 - 1, dir.getY()};
			dir.normalize();
			startMovingTime = SDL_GetTicks();
		}

		Move();
	}

	void Move(){
		position = position + (dir * speed);
	}

	int GetLives() { return actualLives; }

	bool isDead() { return dead; }
};

