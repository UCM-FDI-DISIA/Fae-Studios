#include "MeleeEnemy.h"

void MeleeEnemy::Move() {
	if (!detectPlayer) {
		int frameMovingTime = SDL_GetTicks() - startMovingTime;
		if (frameMovingTime >= NEW_DIR) {
			dir = { (double)(rand() % 3 - 1), dir.getY()};
			dir.normalize();

			if (dir.getX() < 0) lookingRight = false; // Si es 0 se queda mirando según su último movimiento
			else if (dir.getX() > 0) lookingRight = true;
			startMovingTime = SDL_GetTicks();
		}
	}
	else {
		FollowPlayer();
	}

	if (attackState == normal || attackState == preparing) {
		Enemy::Move();
	}
}

void MeleeEnemy::render() const {
	if (dead || attackState == attacking || attackState == afterAttack) {
		texture->renderFrame(getRect(), 0, col, 0, flip[lookingRight]);
	}
	else if (attackState == normal || attackState == preparing) {
		if (dir.getX() == 0 || attackState == preparing) texture->renderFrame(getRect(), 0, (SDL_GetTicks() / time_per_frame) % 3, 0, flip[lookingRight]);
		else texture->renderFrame(getRect(), 0, (SDL_GetTicks() / time_per_frame) % 4 + 3, 0, flip[lookingRight]);
	}
}

void MeleeEnemy::Die() {
	Enemy::Die();
	col = 12;
	timer = SDL_GetTicks();
}


void MeleeEnemy::Attack() {
	Enemy::Attack();
	startMovingTime = SDL_GetTicks();
}

void MeleeEnemy::update() {
	Enemy::update();
	if (!dead) {
		if (attackState == attacking || attackState == afterAttack) {
			if (!attacked) {
				attackStart = SDL_GetTicks();
				attacked = true;
			}
			if (col >= 11) {
				col = 11;
			}
			else
			{
				if (SDL_GetTicks() - attackStart < ATTACKING_TIME / 2) {
					col = 7;
					timer = SDL_GetTicks();
				}
				else col = ((SDL_GetTicks() - timer) / (time_per_frame)) % 5 + 8;
			}
		}
		else {
			attacked = false;
			col = 7;
		}
	}
	else {
		col = ((SDL_GetTicks() - timer) / (time_per_frame)) % 10 + 12;
		if (col >= 21) {
			col = 21;
			deadAnimationEnd = true;
		}

	}

	collider = getCollider();
}

void MeleeEnemy::MoveTriggers() {
	SDL_Rect collider = getCollider();
	if (lookingRight) // Ajuste del trigger en función del movimiento del enemigo
		attackTrigger.x = position.getX()  + width/ 2;
	else
		attackTrigger.x = position.getX();

	attackTrigger.y = position.getY();

	detectingTrigger.x = attackTrigger.x;
	detectingTrigger.y = attackTrigger.y + collider.h / 2 - detectingTrigger.h / 2;
}