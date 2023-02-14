#pragma once
#include "CollisionObject.h"
#include "../utils/Elements.h"

class PlayState;

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
	staticEnemy(Vector2D pos, Texture* texture,GameObject* p, float time, int health, elementsInfo::elements elem, float w = 1.0f, float h = 1.0f, Scale scale = { 1.0f, 1.0f }, GameState* state = nullptr) : CollisionObject(pos, texture, scale, state) {
		shootTime = time;
		maxLives = actualLives = health;
		element = elem;
		trigger.x = pos.getX() - 2 * texture->getW(); trigger.y = pos.getY();
		trigger.w = w; trigger.h = h;
		player = p;
		dead = false;
		startTime = SDL_GetTicks();
	}

	virtual ~staticEnemy() = default;

	void update() override;

	void Damage(elementsInfo::elements e) {
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) Die();
	}

	void Die() {
		dead = true;
		// borrar o marcar booleano para borrar después
	}

	void DetectPlayer();
};

