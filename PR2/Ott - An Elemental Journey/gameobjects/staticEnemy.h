#pragma once
#include "Enemy.h"
#include "../utils/Elements.h"

class PlayState;

class staticEnemy : public Enemy
{
	float shootTime;

public:
	staticEnemy(const Vector2D pos, Texture* texture, GameObject* p, float time, int health, elementsInfo::elements elem, float w = 1.0f, const  Scale scale = { 1.0f, 1.0f }, GameState* state = nullptr) : Enemy(pos, texture, health, elem, p, false, Vector2D(0, 0), scale, w, state) {
		shootTime = time;
		maxLives = actualLives = health;
		element = elem;
		attackTrigger.x = pos.getX() - 2 * texture->getW(); attackTrigger.y = pos.getY();
		attackTrigger.w = w; attackTrigger.h = height;
		player = p;
		dead = false;
		startAttackingTime = SDL_GetTicks();
	}

	virtual ~staticEnemy() = default;

	void update() override;

	void Attack() override;
};

