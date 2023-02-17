#pragma once
#include "../CollisionObject.h"

class Entity;
class Shield: public CollisionObject
{
public:
	Shield(const Vector2D& position, Texture*& texture, const Scale& scale = Scale(1.0f, 1.0f)) :
		CollisionObject(position, texture, scale) {};
	virtual ~Shield() = default;
	void move(int x, int y, float witdh, bool lookingFront);
	virtual void render(const SDL_Rect& Camera);
	inline Texture* getTexture() { return texture; }
	inline void changeTexture(Texture* t) { texture = t; }
	bool collide(Entity* ent);
};

