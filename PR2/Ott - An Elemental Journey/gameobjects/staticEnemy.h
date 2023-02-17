#pragma once
#include "Enemy.h"
#include "../utils/Elements.h"

class PlayState;

class staticEnemy : public Enemy
{
	float shootTime;
public:
	staticEnemy(Vector2D pos, Texture* texture,GameObject* p, float time, int health, elementsInfo::elements elem, float wTrigger = 110.0f, float hTrigger = 100, const Scale scale = { 1.0f, 1.0f }, GameState* state = nullptr) : Enemy(pos, texture, health, elem, p, false, Vector2D(0, 0), scale, wTrigger, hTrigger, state) {
		shootTime = time;
		attackTrigger.x = pos.getX() - 2 * texture->getW(); attackTrigger.y = pos.getY();
		attackTrigger.w = wTrigger; attackTrigger.h = height;
		startAttackingTime = SDL_GetTicks();
	}

	virtual ~staticEnemy() = default;

	void update() override;

	void Attack();
};

