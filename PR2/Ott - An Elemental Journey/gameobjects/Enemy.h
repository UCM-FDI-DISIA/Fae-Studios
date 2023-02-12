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
	Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, Vector2D dir = Vector2D(0,0), const Scale& scale = Scale(1.0f, 1.0f), float w = 110.0f, float h = 100.0f): MovingObject(position, texture, dir, scale), actualLives(lives), element(elem), player(p) {
		maxLives = lives * 2;  // Representación interna doblada
		actualLives = lives * 2;
		speed = 0.1;

		attackTrigger.x = position.getX() + width; attackTrigger.y = position.getY();
		attackTrigger.w = w; attackTrigger.h = h;
		attackState = normal;

		detectingTrigger.x = position.getX() + width; detectingTrigger.y = position.getY();
		detectingTrigger.w = 2 * w; detectingTrigger.h = h;
		detectPlayer = false;

		movee = moving;
		player = p;
	}
	~Enemy() {

	}

	void Damage(elementsInfo::elements e) {
		cout << "Hit" << endl;
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) Die();
	}

	void Die() {
		dead = true;
		std::cout << "Muerto" << endl;
		// borrar o marcar booleano para borrar después
	}

	void DetectPlayer() {
		SDL_Rect playerRect = player->getRect();
		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (!detectPlayer) {
			if(SDL_HasIntersection(&detectingTrigger, &playerRect)) detectPlayer = true;
			if(detectPlayer) cout << "Detected" << endl;
		}
		else {
			if (attackState == normal && SDL_HasIntersection(&attackTrigger, &playerRect)) {
				attackState = preparing;
				startAttackingTime = SDL_GetTicks();
			}
			else if (attackState == preparing && frameTime >= PREPARING_TIME) {
				cout << attackState << endl;
				attackState = attacking;
				startAttackingTime = SDL_GetTicks();
			}
			else if (attackState == attacking && frameTime >= ATTACKING_TIME) {
				cout << attackState << endl;
				if (SDL_HasIntersection(&attackTrigger, &playerRect))
					static_cast<Enemy*>(player)->Damage(element);
				attackState = normal;
			}
		}
	}

	void FollowPlayer() {
		// Distancia de seguridad para comprobar que no se pega al jugador
		if (lookingRight && abs(player->getRect().x - (position.getX() + width)) > nearDistance ||
			!lookingRight && abs(player->getRect().x - position.getX()) > nearDistance) {
			dir = { player->getRect().x - dir.getX(), dir.getY() };
			dir.normalize();
		}
		else {
			dir = { 0, dir.getY()};
			dir.normalize();
		}
	}

	virtual void update() { //Falta el movimiento del enemigo
		if (!movee) {
			return;
		}

		DetectPlayer();
		int frameMovingTime = SDL_GetTicks() - startMovingTime;

		if (lookingRight) // Ajuste del trigger en función del movimiento del enemigo
			attackTrigger.x = position.getX() + width;
		else
			attackTrigger.x = position.getX() - attackTrigger.w;


		attackTrigger.y = position.getY();

		detectingTrigger.x = attackTrigger.x;
		detectingTrigger.y = attackTrigger.y;

		if (!detectPlayer) {
			if (frameMovingTime >= NEW_DIR) {
				dir = { (double)(rand() % 3 - 1), dir.getY()};  // No se puede declarar con parentesis, 
				// tiene que ser con llaves o con Vector2D(rand() % 3 - 1, dir.getY()).
				// El módulo tiene que ser entre 3 para poder tener 3 valores, (0, 1, 2). Al restar -1 se queda en (-1, 0, 1)
				dir.normalize();

				if (dir.getX() < 0) lookingRight = false; // Si es 0 se queda mirando según su último movimiento
				else if (dir.getX() > 0) lookingRight = true;
				startMovingTime = SDL_GetTicks();
			}
		}
		else {
			FollowPlayer();
		}

		Move();
	}

	void Move(){
		position = position + dir * speed; // No es (position + dir) * speed porque la posición se multiplicaría por la velocidad
		// en vez de que se multiplique solo la dirección, asi que se teletransportaría
	}

	int GetLives() { return actualLives; }

	bool isDead() { return dead; }
};

