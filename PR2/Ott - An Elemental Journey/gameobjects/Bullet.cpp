#include "Bullet.h"

void Bullet::update()
{
	position = position + dir * speed;
	Collision();
}

void Bullet::Collision()
{
	SDL_Rect playerRect = player->getRect();
	SDL_Rect bulletRect = getRect();
	if (SDL_HasIntersection(&bulletRect, &playerRect)) {
		static_cast<Enemy*>(player)->Damage(element);
		dead = true;
		deleteMyself();
	}
	else {
		if (position.getX() < 0 || position.getX() > 800)
			dead = true;
	}
}
