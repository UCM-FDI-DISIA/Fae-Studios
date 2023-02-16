#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy {
public:
	MeleeEnemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p,
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float wTrigger = 110.0f, float hTrigger = 100, GameState* state = nullptr) :
		Enemy(position, texture, lives, elem, p, moving, dir, scale, wTrigger, hTrigger, state) {};

	virtual void Move();
};