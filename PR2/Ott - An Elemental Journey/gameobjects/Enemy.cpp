#include "Enemy.h"
#include "../gameflow/GameState.h"
#include "../gameflow/PlayState.h"


Enemy::Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, Vector2D dir, const Scale& scale, float w, GameState* state) : MovingObject(position, texture, dir, scale, state), actualLives(lives), element(elem), player(p) {
	maxLives = lives * 2;  // Representación interna doblada
	actualLives = lives * 2;
	speed = 0.3;

	attackTrigger.x = position.getX() + width; attackTrigger.y = position.getY();
	attackTrigger.w = w; attackTrigger.h = height;
	attackState = normal;

	detectingTrigger.x = position.getX() + width; detectingTrigger.y = position.getY();
	detectingTrigger.w = 2 * w; detectingTrigger.h = height;
	detectPlayer = false;

	movee = moving; // TEMPORAL, BORRAR
	player = p;
}

bool Enemy::Damage(elementsInfo::elements e) {
	cout << "Hit" << endl;
	actualLives -= elementsInfo::matrix[e][element];
	if (actualLives <= 0) {
		Die();
		return true;
	}
	else return false;
}

void Enemy::Die() {
	dead = true;
	std::cout << "Muerto" << endl;
	deleteMyself();
}

void Enemy::DetectPlayer() {
	/*
	if (!detectPlayer && player != nullptr) {
		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (SDL_HasIntersection(&detectingTrigger, &playerRect)) detectPlayer = true;
		
	}
	else if (detectPlayer) {
		
	}*/
	if (player != nullptr) {
		SDL_Rect playerRect = player->getRect();
		detectPlayer = SDL_HasIntersection(&detectingTrigger, &playerRect);
		if (detectPlayer) cout << "Detected" << endl;
	}
}

void Enemy::DetectAttackTrigger() {
	if (detectPlayer && player != nullptr) {
		SDL_Rect playerRect = player->getRect();
		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (attackState == normal && SDL_HasIntersection(&attackTrigger, &playerRect)) {
			attackState = preparing;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == preparing && frameTime >= PREPARING_TIME) {
			cout << attackState << endl;
			attackState = attacking;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == attacking && frameTime >= ATTACKING_TIME) {
			cout << attackState << endl;
			Attack();
			attackState = normal;
		}
	}
}

void Enemy::Attack() {
	SDL_Rect playerRect = player->getRect();
	if (SDL_HasIntersection(&attackTrigger, &playerRect)) {
		if (static_cast<Enemy*>(player)->Damage(element)) {
			player = nullptr;
			detectPlayer = false;
		}
	}
}


void Enemy::FollowPlayer() {
	// Distancia de seguridad para comprobar que no se pega al jugador
	if (lookingRight && abs(player->getRect().x - (position.getX() + width)) > nearDistance ||
		!lookingRight && abs(player->getRect().x - position.getX()) > nearDistance) {
		dir = { player->getRect().x - position.getX(), dir.getY()};
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

	if (!grounded) {
		useGravity();
	}
	SDL_Rect result = {0,0,0,0};
	static_cast<PlayState*> (actualState)->enemyCollidesGround(getRect(), result, grounded);
	
	if (grounded) {
		ChangeDir(result);
		position = { position.getX(), position.getY() - result.h };
	}

	DetectPlayer();
	DetectAttackTrigger();

	MoveTriggers();
	
	Move();
}

void Enemy::ChangeDir(const SDL_Rect& result){
	if (!detectPlayer && result.w < width * turningOffset) {
		if (abs(result.x - position.getX()) < turningError) dir = { -1, dir.getY() };
		else dir = { 1, dir.getY() };

		dir.normalize();
	}
}

void Enemy::playerCollide() {
	if (player != nullptr) {
		SDL_Rect myRect = getRect();
		SDL_Rect playerRect = player->getRect();
		if (SDL_HasIntersection(&myRect, &playerRect)) {
			if (static_cast<Enemy*>(player)->Damage(element)) { // Falta implementar lo de la invulnerabilidad
				player = nullptr;
				detectPlayer = false;
			}
		}
	}
}

void Enemy::MoveTriggers() {
	if (lookingRight) // Ajuste del trigger en función del movimiento del enemigo
		attackTrigger.x = position.getX() + width;
	else
		attackTrigger.x = position.getX() - attackTrigger.w;

	attackTrigger.y = position.getY();

	detectingTrigger.x = attackTrigger.x;
	detectingTrigger.y = attackTrigger.y;
}


void Enemy::Move() {
	position = position + dir * speed; 
	SDL_Rect result = { 0,0,0,0 };
	bool collided = false;
	static_cast<PlayState*> (actualState)->enemyCollidesWall(getRect(), result, collided);
	if (collided) {
		if (dir.getX() > 0) position = { position.getX() - result.w, position.getY()};
		else position = { position.getX() + result.w, position.getY()};
		if(!detectPlayer)
			dir = { dir.getX() * -1, dir.getY() };
	}
	playerCollide();
}



int Enemy::GetLives() { return actualLives; }

bool Enemy::isDead() { return dead; }

void Enemy::useGravity() {
	position = position + Vector2D(0, 1 + static_cast<PlayState*> (actualState)->Gravity());
}
