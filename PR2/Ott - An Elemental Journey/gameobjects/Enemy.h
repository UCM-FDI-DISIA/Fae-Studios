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
	int startTime = 0;
	SDL_Rect Trigger;
	triggerState state;
public:
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, Vector2D dir = Vector2D(0,0), const Scale& scale = Scale(1.0f, 1.0f), float w = 1.0f, float h = 1.0f): MovingObject(position, texture, dir, scale), actualLives(lives), element(elem) {
		maxLives = lives * 2;  // Representación interna doblada
		actualLives = lives * 2;
		Trigger.x = position.getX() - w; Trigger.y = position.getY();
		Trigger.w = w; Trigger.h = h;
		state = normal;
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

	void OnEnter() {
		if (state == normal) {
			state = preparing;
		}
		else if (state == attacking) {
			//Player.Damage(element) supongo
		}
	}

	virtual void update() { //Falta el movimiento del enemigo
		int frameTime = startTime - SDL_GetTicks();
		if (state == preparing && frameTime >= PREPARING_TIME) {
			state = attacking;
			startTime = SDL_GetTicks();
		}
		else if (state == attacking && frameTime >= ATTACKING_TIME) {
			state = normal;
			startTime = SDL_GetTicks();
		}

		Trigger.x = (position.getX() - Trigger.w); //Habría que multiplicarlo por el vector de dirección del enemigo para saber si hay que ponerlo delante o detrás de él
		Trigger.y = position.getY();
	}

	int GetLives() { return actualLives; }

	bool isDead() { return dead; }
};

