#pragma once
#include "Enemy.h"
#include "../utils/Elements.h"

class PlayState;

class staticEnemy : public Enemy
{
	float shootTime;
	int attackStart = 0;
	bool shooted = false;
public:
	staticEnemy(Vector2D pos, Texture* texture,GameObject* p, float time, int health, elementsInfo::elements elem, float wTrigger = 110.0f, float hTrigger = 100, const Scale scale = { 1.0f, 1.0f }, PlayState* state = nullptr, Texture* colliderDEBUG = nullptr) : 
		Enemy(pos, texture, health, elem, p, false, state, Vector2D(0, 0), scale, wTrigger, hTrigger, colliderDEBUG) {
		shootTime = time;
		attackTrigger.x = pos.getX() - 2 * texture->getW(); attackTrigger.y = pos.getY();
		attackTrigger.w = wTrigger; attackTrigger.h = height;
		startAttackingTime = SDL_GetTicks();
		colliderWH = { (double)(width * 0.5), (double)(height * 0.6) };
		colliderOffset = { (double)(width * 0.3),(double)(height * 0.35)};
	}

	virtual ~staticEnemy() = default;

	virtual void update();

	void Attack();

	virtual void render(const SDL_Rect& Camera = { 0,0,0,0 }) const;
};

