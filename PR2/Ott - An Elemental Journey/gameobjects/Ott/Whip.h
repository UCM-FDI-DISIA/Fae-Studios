#pragma once
#include "../../Src/Entity.h"
class Whip: public CollisionObject
{
private:
	//Texture* texture;
public:
	Whip(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) :
		CollisionObject(position, texture, scale){};
	virtual ~Whip() = default;
	void move(int x, int y, float witdh, bool lookingFront);
	virtual void render(const SDL_Rect& Camera);
	void damage(Entity* e);
	inline Texture* getTexture() { return texture; }
};

