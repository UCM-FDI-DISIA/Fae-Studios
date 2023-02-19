#include "Enemy.h"
#include "../gameflow/GameState.h"
#include "../gameflow/play/PlayState.h"
#include "Ott/Ott.h"

Enemy::Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, PlayState* game, Vector2D dir, const Scale& scale, float wTrigger, float hTrigger) : Entity(position, texture, dir, lives, game,  scale), actualLives(lives), element(elem), player(p) {
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

	speed = { 0,0 };
}

bool Enemy::recieveDamage(elementsInfo::elements elem) {
	cout << "Hit " << actualLives << endl;
	actualLives -= elementsInfo::matrix[elem][element];
	startDamagedTime = SDL_GetTicks();
	if (actualLives <= 0) {
		die();
		return true;
	}
	else return false;
}

void Enemy::die() {
	if(!dead) timer = SDL_GetTicks();
	Entity::die();
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
		if(player != nullptr) playerRect = static_cast<Ott*> (player)->getRect();
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
		SDL_Rect playerRect = static_cast<Ott*> (player)->getRect();
		if (SDL_HasIntersection(&attackTrigger, &playerRect)) {
			if (static_cast<Ott*>(player)->recieveDamage(element)) { player = nullptr; detectPlayer = false; }
		}
	}
}


void Enemy::FollowPlayer() {
	// Distancia de seguridad para comprobar que no se pega al jugador
	SDL_Rect collider = getCollider();
	SDL_Rect ott = static_cast<Ott*> (player)->getRect();
	if (lookingRight && abs(ott.x - (collider.x + collider.w)) > nearDistance ||
		!lookingRight && abs(ott.x + collider.w - collider.x) > nearDistance) {

		if ((double)ott.x - collider.x > 0) {
			speed = { horizontalSpeed, speed.getY() };
			lookingRight = true;
		}
		else {
			speed = { -horizontalSpeed, speed.getY() };
			lookingRight = false;
		}
	}
	else {
		speed = { 0, speed.getY() };
	}
}

void Enemy::update() {
	if (!movee) { // TEMPORAL, BORRAR
		return;
	}
	if (!dead) {
	
		DetectPlayer();
		DetectAttackTrigger();

		MoveTriggers();
	
		Move();

		if (SDL_GetTicks() - startDamagedTime < DAMAGED_TIME) {
			fil = 1;
		}
		else fil = 0;
	}
}

void Enemy::ChangeDir(const SDL_Rect& result){
	if (!detectPlayer && result.w < getCollider().w * turningOffset) {
		if (abs(result.x - getCollider().x) < turningError) {
			speed = { -horizontalSpeed, speed.getY() };
			lookingRight = false;
		}
		else {
			speed = { horizontalSpeed, speed.getY() };
			lookingRight = true;
		}
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
	position = position + speed; 
	bool collided = false;
	SDL_Rect groundRect, colRect;
	groundCollider = getRect();
	groundCollider.y += groundCollider.h;
	groundCollider.h = 10;
	groundCollider.w /= 2;
	groundCollider.x += groundCollider.w / 2;
	
	if (!grounded) {
		useGravity();
	}
	game->enemyCollide(getCollider(), groundCollider, groundRect, colRect, grounded, collided, speed);

	if (grounded) {
		ChangeDir(groundRect);
		position = { position.getX(), groundRect.y - (double)height };
	}

	if (collided) {
		if (abs(colRect.x - getCollider().x) < turningError) {
			position = { position.getX() + colRect.w, position.getY() };
			if(!detectPlayer){
				speed = { horizontalSpeed, speed.getY() };
				lookingRight = true;
			}
		}
		else {
			position = { position.getX() - colRect.w, position.getY() };
			if (!detectPlayer) {
				speed = { -horizontalSpeed, speed.getY() };
				lookingRight = false;
			}
		}
	}
	playerCollide();
}

int Enemy::GetLives() { return actualLives; }

bool Enemy::isDead() { return dead; }

void Enemy::useGravity() {
	position = position + Vector2D(0, 1 + game->Gravity());
}
