#pragma once
#include "Enemy.h"

class MeleeEnemy : public Enemy {
public:
	MeleeEnemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p,
		bool moving, Vector2D dir = Vector2D(0, 0), const Scale& scale = Scale(1.0f, 1.0f), float w = 110.0f, GameState* state = nullptr) :
		Enemy(position, texture, lives, elem, p, moving, dir, scale, w, state) {};

	virtual void Move();
};