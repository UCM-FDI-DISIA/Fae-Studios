#pragma once
#include "Enemy.h"
#include "../utils/Elements.h"
class Bullet : public Entity
{
private:
	elementsInfo::elements element;
	GameObject* player;

	bool dead = false;
public:
	Bullet(const Vector2D& position, Texture* texture, elementsInfo::elements elem, GameObject* p, Vector2D dir, const Scale& scale, PlayState* state) : 
		Entity(position, texture, dir, 10, game, scale), element(elem), player(p) {
		speed = dir;
	};
	virtual ~Bullet() = default;

	void update() override;

	void Collision();
};