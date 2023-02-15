#pragma once
#include "../Entity.h"
class Whip: public CollisionObject
{
public:
	Whip(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) :
		CollisionObject(position, texture, scale) {};
	virtual ~Whip() = default;
	void move(int x, int y, float witdh, bool lookingFront);
	virtual void render(const SDL_Rect& Camera);
	void damage(Entity* e);
};

