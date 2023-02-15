#include "Shield.h"
void Shield::move(int x, int y, float width, bool lookingFront)
{
	if (!lookingFront)
	{
		position = Vector2D(x - width / 3, y);
	}
	else position = Vector2D(x + width / 2, y);
}
void Shield::render(const SDL_Rect& Camera)
{
	GameObject::render(Camera);
}