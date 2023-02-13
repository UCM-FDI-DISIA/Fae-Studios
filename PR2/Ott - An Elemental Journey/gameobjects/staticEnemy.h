#pragma once
#include "CollisionObject.h"
#include "../utils/Elements.h"
class staticEnemy : public CollisionObject
{
	float shootTime;
	int maxLives;
	int actualLives;
	elementsInfo::elements element;
	bool dead;
	GameObject* player;
	int startTime = 0;

	SDL_Rect trigger;
public:
	staticEnemy(Vector2D pos, Texture* texture,GameObject* p, float time, int health, elementsInfo::elements elem, float w = 1.0f, float h = 1.0f, Scale scale = { 1.0f, 1.0f }) : CollisionObject(pos, texture, scale) {
		shootTime = time;
		maxLives = actualLives = health;
		element = elem;
		trigger.x = pos.getX() - texture->getW(); trigger.y = pos.getY();
		trigger.w = w; trigger.h = h;
		player = p;
		dead = false;
	}

	void Damage(elementsInfo::elements e) {
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) Die();
	}

	void Die() {
		dead = true;
		// borrar o marcar booleano para borrar después
	}

	void DetectPlayer() {
		SDL_Rect playerRect = player->getRect();
		if (SDL_HasIntersection(&trigger, &playerRect)) {
			startTime = SDL_GetTicks();
			if (SDL_GetTicks() - startTime >= shootTime) {
				//new Disparo :)
				startTime = SDL_GetTicks();
			}
		}
	}
};

