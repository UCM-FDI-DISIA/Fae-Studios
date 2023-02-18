#include "Whip.h"
void Whip::move(int x, int y, float width, bool lookingFront)
{
	y += 20;
	if (!lookingFront)
	{
		position = Vector2D(x +- width * 2, y);
	}
	else position = Vector2D(x + width - 20, y);
}
void Whip::render(const SDL_Rect& Camera)
{
	GameObject::render(Camera);
}

void Whip::damage(Entity* e)
{
	e->recieveDamage(1); //a lo mejor mo es 1, habría que poner el tipo de tierra :)
}
