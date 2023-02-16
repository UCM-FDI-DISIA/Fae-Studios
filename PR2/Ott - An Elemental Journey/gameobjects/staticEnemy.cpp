#include "staticEnemy.h"
#include "../gameflow/PlayState.h"

void staticEnemy::update()
{
	DetectPlayer();
}

void staticEnemy::Attack(){
	SDL_Rect playerRect = player->getRect();

	if (SDL_GetTicks() - startAttackingTime >= shootTime) {
		if (playerRect.x < position.getX()) {
			static_cast<PlayState*>(actualState)->addBullet(position, Vector2D(-1, 0), element, player);
		}
		else
			static_cast<PlayState*>(actualState)->addBullet(position + getRect().w, Vector2D(1, 0), element, player);

		startAttackingTime = SDL_GetTicks();
	}
}
