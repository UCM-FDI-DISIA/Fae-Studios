#pragma once
#include "Enemy.h"
#include "../utils/Elements.h"
class Bullet : public MovingObject
{
private:
	elementsInfo::elements element;
	GameObject* player;

	bool dead = false;
public:
	Bullet(const Vector2D& position, Texture* texture, elementsInfo::elements elem, GameObject* p, Vector2D dir, const Scale& scale, GameState* state) : MovingObject(position, texture, dir, scale, state), element(elem), player(p) {};
	virtual ~Bullet() = default;

	void update() override;

	void Collision();
};

