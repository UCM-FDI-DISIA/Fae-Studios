#include "staticEnemy.h"
#include "../gameflow/PlayState.h"

void staticEnemy::update()
{
	if (!dead) {
		cout << col << endl;
		DetectPlayer();
		Attack();
	}
	else {
		col = ((SDL_GetTicks() - timer) / (time_per_frame)) % 21 + 9;
		if (col >= 20) {
			col = 20;
			deleteMyself();
		}
	}
}

void staticEnemy::Attack(){

	int timer = SDL_GetTicks() - startAttackingTime;
	if (detectPlayer) {
		if (timer >= shootTime && col > 4) {
			SDL_Rect playerRect = player->getRect();
			if (!shooted) {
				if (playerRect.x < position.getX()) {
					static_cast<PlayState*>(actualState)->addBullet({ position.getX(), position.getY() + height * 0.8}, Vector2D(-1, 0), element, player);
					shooted = true;
					cout << "AAA";
				}
				else {
					static_cast<PlayState*>(actualState)->addBullet({ position.getX() + width * 0.8, position.getY() + height * 0.8 }, Vector2D(1, 0), element, player);
					shooted = true;
					cout << "BBB";
				}
			}
			if (col != 9) col = ((SDL_GetTicks() - attackStart) / time_per_frame) % 4 + 6;
			else {
				col = 1; startAttackingTime = SDL_GetTicks(); attackStart = SDL_GetTicks(); shooted = false;
			}
		}
		else if (timer < shootTime * 0.8) {
			col = (SDL_GetTicks() / time_per_frame) % 2;
			attackStart = SDL_GetTicks();
		}
		else {
			if (col >= 5) {
				col = 5; attackStart = SDL_GetTicks();
			}
			else col = ((SDL_GetTicks() - attackStart) / time_per_frame) % 4 + 2;
		}
	}
	else {
		col = (SDL_GetTicks() / time_per_frame) % 2;
		attackStart = SDL_GetTicks();
	}
}

void staticEnemy::render() const {
	texture->renderFrame(getRect(), 0, col);
}
