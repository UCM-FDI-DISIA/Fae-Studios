#pragma once
#include "GameObject.h"

class CollisionObject : public GameObject
{
protected:

public:
	CollisionObject(Vector2D pos, Texture* texture, Scale scale = Scale(1.0f, 1.0f));
	~CollisionObject();

	bool collide(const SDL_Rect& obj, SDL_Rect& result);
};

