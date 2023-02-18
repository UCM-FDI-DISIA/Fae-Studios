#include "Enemy.h"
#include "../gameflow/GameState.h"
#include "../gameflow/PlayState.h"


Enemy::Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, Vector2D dir, const Scale& scale, float wTrigger, float hTrigger, GameState* state) : MovingObject(position, texture, dir, scale, state), actualLives(lives), element(elem), player(p) {
	maxLives = lives * 2;  // Representación interna doblada
	actualLives = lives * 2;
	speed = 0.3;

	attackTrigger.x = position.getX() + width; attackTrigger.y = position.getY();
	attackTrigger.w = wTrigger; attackTrigger.h = height;
	attackState = normal;

	detectingTrigger.x = position.getX() + width; detectingTrigger.y = position.getY() + height / 2 - hTrigger / 2;
	detectingTrigger.w = 2 * wTrigger; detectingTrigger.h = hTrigger;
	detectPlayer = false;

	movee = moving; // TEMPORAL, BORRAR
	player = p;
	
	colliderOffset = { 0,0 };
	colliderWH = { (double)width, (double)height };

	if(player != nullptr) nearDistance = width;
}

bool Enemy::Damage(elementsInfo::elements e) {
	cout << "Hit " << actualLives << endl;
	actualLives -= elementsInfo::matrix[e][element];
	if (actualLives <= 0) {
		Die();
		return true;
	}
	else return false;
}

void Enemy::Die() {
	dead = true;
	timer = SDL_GetTicks();
}

void Enemy::DetectPlayer() {
	/*if (!detectPlayer && player != nullptr) {
		SDL_Rect playerRect = player->getRect();
		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (SDL_HasIntersection(&detectingTrigger, &playerRect)) detectPlayer = true;
		if (detectPlayer) cout << "Detected" << endl;
	}*/
	if (player != nullptr) {
		SDL_Rect playerRect = player->getRect();
		detectPlayer = SDL_HasIntersection(&detectingTrigger, &playerRect);
	}
}

void Enemy::DetectAttackTrigger() {
	if (detectPlayer && player != nullptr || attackState != normal) {
		SDL_Rect playerRect = { 0,0,0,0 };
		if(player != nullptr) playerRect = static_cast<Enemy*> (player)->getCollider();
		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (attackState == normal && frameTime >= PREPARING_TIME && SDL_HasIntersection(&attackTrigger, &playerRect)) {
			attackState = preparing;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == preparing && frameTime >= PREPARING_TIME) {
			attackState = attacking;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == attacking && frameTime >= ATTACKING_TIME / 2) {
			Attack();
			attackState = afterAttack;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == afterAttack && frameTime >= ATTACKING_TIME / 2) {
			attackState = normal;
			startAttackingTime = SDL_GetTicks();
		}
	}
	else attackState = normal;
}

void Enemy::Attack() {
	if (player != nullptr) {
		SDL_Rect playerRect = static_cast<Enemy*> (player)->getCollider();
		if (SDL_HasIntersection(&attackTrigger, &playerRect)) {
			if (static_cast<Enemy*>(player)->Damage(element)) {
				player = nullptr;
				detectPlayer = false;
			}
		}
	}
}


void Enemy::FollowPlayer() {
	// Distancia de seguridad para comprobar que no se pega al jugador
	SDL_Rect collider = getCollider();
	SDL_Rect ott = static_cast<Enemy*> (player)->getCollider();
	if (lookingRight && abs(ott.x - (collider.x + collider.w)) > nearDistance ||
		!lookingRight && abs(ott.x + collider.w - collider.x) > nearDistance) {
		dir = { (double)(ott.x - collider.x), dir.getY()};
		dir.normalize();
	}
	else {
		dir = { 0, dir.getY() };
		dir.normalize();
	}
}

void Enemy::update() {
	if (!movee) { // TEMPORAL, BORRAR
		return;
	}
	if (!dead) {
		if (!grounded) {
			useGravity();
		}
		SDL_Rect result = {0,0,0,0};
		static_cast<PlayState*> (actualState)->enemyCollidesGround(getCollider(), result, grounded);
	
		if (grounded) {
			ChangeDir(result);
			position = { position.getX(), position.getY() - result.h };
		}

		DetectPlayer();
		DetectAttackTrigger();

		MoveTriggers();
	
		Move();
	}
}

void Enemy::ChangeDir(const SDL_Rect& result){
	if (!detectPlayer && result.w < getCollider().w * turningOffset) {
		if (abs(result.x - getCollider().x) < turningError) {
			dir = { -1, dir.getY() }; 
			lookingRight = false;
		}
		else {
			dir = { 1, dir.getY() };
			lookingRight = true;
		}

		dir.normalize();
	}

}

void Enemy::playerCollide() {
	/*if (player != nullptr) {
		SDL_Rect myRect = getCollider();
		SDL_Rect playerRect = static_cast<Enemy*> (player)->getCollider();
		if (SDL_HasIntersection(&myRect, &playerRect)) {
			if (static_cast<Enemy*>(player)->Damage(element)) { // Falta implementar lo de la invulnerabilidad
				player = nullptr;
				detectPlayer = false;
			}
		}
	}*/
}

void Enemy::MoveTriggers() {
	SDL_Rect collider = getCollider();
	if (lookingRight) // Ajuste del trigger en función del movimiento del enemigo
		attackTrigger.x = collider.x + collider.w;
	else
		attackTrigger.x = collider.x - attackTrigger.w;

	attackTrigger.y = collider.y;

	detectingTrigger.x = attackTrigger.x;
	detectingTrigger.y = attackTrigger.y + collider.h/2 - detectingTrigger.h/2;
}


void Enemy::Move() {
	position = position + dir * speed; 
	SDL_Rect result = { 0,0,0,0 };
	bool collided = false;
	static_cast<PlayState*> (actualState)->enemyCollidesWall(getCollider(), result, collided);
	if (collided) {
		if (abs(result.x - getCollider().x) < turningError) {
			position = { position.getX() + result.w, position.getY() };
			if(!detectPlayer){
				dir = { 1, dir.getY() };
				lookingRight = true;
			}
		}
		else {
			position = { position.getX() - result.w, position.getY() };
			if (!detectPlayer) {
				dir = { -1, dir.getY() };
				lookingRight = false;
			}
		}
		dir.normalize();
	}
	playerCollide();
}



int Enemy::GetLives() { return actualLives; }

bool Enemy::isDead() { return dead; }

void Enemy::useGravity() {
	position = position + Vector2D(0, 1 + static_cast<PlayState*> (actualState)->Gravity());
}
