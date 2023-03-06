#pragma once
#include "Enemy.h"
#include "../utils/Elements.h"
class Bullet : public Entity
{
private:
	elementsInfo::elements element;
	GameObject* player;
	bool lookingRight;
	SDL_RendererFlip flip[2] = {SDL_FLIP_HORIZONTAL, SDL_FLIP_NONE};

	bool dead = false;
public:
	Bullet(const Vector2D& position, Texture* texture, elementsInfo::elements elem, GameObject* p, Vector2D dir, const Scale& scale, PlayState* state) : 
		Entity(position, texture, dir, 10, state, scale), element(elem), player(p) {
		speed = dir;
	};
	virtual ~Bullet() = default;

	void update() override;

	void Collision();

	virtual void render(const SDL_Rect& Camera = { 0,0,0,0 }) const;
};