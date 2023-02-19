#include "Bullet.h"
#include "../gameobjects/Ott/Ott.h"

void Bullet::update()
{
	position = position + speed;
	Collision();
}

void Bullet::Collision()
{
	SDL_Rect playerRect = player->getRect();
	SDL_Rect result;
	if (collide(playerRect, result)) {
		static_cast<Ott*>(player)->recieveDamage(element, result);
		dead = true;
		deleteMyself();
	}
	else if (game->bulletCollide(getRect())) {
		dead = true;
		deleteMyself();
	}
	else {
		if (position.getX() < 0 || position.getX() > 800)
			dead = true;
	}
}
