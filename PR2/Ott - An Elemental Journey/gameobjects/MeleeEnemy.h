#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy {
private:
	bool attacked = false;
	int attackStart = 0;
	int lastDir = 0;
public:
	MeleeEnemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p,
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110.0f, float hTrigger = 100, PlayState* state = nullptr, Texture* colliderDEBUG = nullptr) :
				Enemy(position, texture, lives, elem, p, moving, state, dir, scale, wTrigger, hTrigger, colliderDEBUG) {
		


		colliderOffset = { (double)(width * 0.40), (double)(height * 0.2) };
		colliderWH = { (double)(width * 0.20), (double)(height * 0.8)};

		nearDistance = colliderWH.getX() * 2;
		attackTrigger = { 0,0, (int)width / 2, (int)height };
	};

	virtual void Move();

	virtual void render(const SDL_Rect& Camera = { 0,0,0,0 }) const;

	virtual void Attack();

	void update();

	virtual void MoveTriggers();

	void die();

};