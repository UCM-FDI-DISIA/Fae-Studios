#pragma once
#include "GameObject.h"

class CollisionObject : public GameObject
{
protected:

public:
	CollisionObject(Vector2D pos, Texture* texture, Scale scale = Scale(1.0f, 1.0f), GO_TYPE type = DEFAULT);
	virtual ~CollisionObject() {};

	virtual bool collide(const SDL_Rect& obj, SDL_Rect& result);
	virtual bool collide(GameObject* c);
};

