#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy {
private:
	bool attacked = false;
	int attackStart = 0;
	int lastDir = 0;
public:
	MeleeEnemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p,
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110.0f, float hTrigger = 100, PlayState* state = nullptr, Texture* te = nullptr) :
				Enemy(position, texture, lives, elem, p, moving, state, dir, scale, wTrigger, hTrigger) {
		


		colliderOffset = {21 * scale.widthScale, 4 * scale.heightScale};
		colliderWH = { (double)(width * 0.45), height * 0.875};

		nearDistance = colliderWH.getX();
		attackTrigger = { 0,0, (int)width / 2, (int)height };
	};

	virtual void Move();

	virtual void render(const SDL_Rect& Camera = { 0,0,0,0 }) const;

	virtual void Attack();

	void update();

	virtual void MoveTriggers();

	void die();

};