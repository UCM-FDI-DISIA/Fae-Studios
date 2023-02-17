#include "Shield.h"
#include "../Entity.h"
#include <iostream>

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
bool Shield::collide(Entity* ent)
{
	SDL_Rect shieldR = getRect();
	SDL_Rect entR = ent->getRect();

	if (SDL_HasIntersection(&shieldR, &entR))
	{
		if (ent->getCurrentElement() == 0)
		{
			cout << "LUZ" << endl;

		}
		else if (ent->getCurrentElement() == 1)
		{
			cout << "FUEGO" << endl;

		}
		else if (ent->getCurrentElement() == 2)
		{
			cout << "AGUA" << endl;

		}
		else if (ent->getCurrentElement() == 3)
		{
			cout << "TIERRA" << endl;

		}
		return true;
	}
}