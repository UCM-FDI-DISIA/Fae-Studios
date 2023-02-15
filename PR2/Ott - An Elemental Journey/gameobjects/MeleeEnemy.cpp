#include "MeleeEnemy.h"

void MeleeEnemy::Move() {
	if (!detectPlayer) {
		int frameMovingTime = SDL_GetTicks() - startMovingTime;
		if (frameMovingTime >= NEW_DIR) {
			dir = { (double)(rand() % 3 - 1), dir.getY() };  // No se puede declarar con parentesis, 
			// tiene que ser con llaves o con Vector2D(rand() % 3 - 1, dir.getY()).
			// El módulo tiene que ser entre 3 para poder tener 3 valores, (0, 1, 2). Al restar -1 se queda en (-1, 0, 1)
			dir.normalize();

			if (dir.getX() < 0) lookingRight = false; // Si es 0 se queda mirando según su último movimiento
			else if (dir.getX() > 0) lookingRight = true;
			startMovingTime = SDL_GetTicks();
		}
	}
	else {
		FollowPlayer();
	}

	Enemy::Move();
}