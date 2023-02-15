#include "staticEnemy.h"
#include "../gameflow/PlayState.h"

void staticEnemy::update()
{
	DetectPlayer();
}

void staticEnemy::DetectPlayer(){
	SDL_Rect playerRect = player->getRect();
	if (SDL_HasIntersection(&trigger, &playerRect)) {
		std::cout << SDL_GetTicks() - startTime << std::endl;
		if (SDL_GetTicks() - startTime >= shootTime) {
			if (playerRect.x < position.getX()) {
				static_cast<PlayState*>(actualState)->addBullet(position, Vector2D(-1, 0), element, player);
			}
			else
				static_cast<PlayState*>(actualState)->addBullet(position + getRect().w, Vector2D(1, 0), element, player);

			startTime = SDL_GetTicks();
		}
	}
}
