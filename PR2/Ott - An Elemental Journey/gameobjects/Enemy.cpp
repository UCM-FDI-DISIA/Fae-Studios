#include "Enemy.h"
#include "../gameflow/GameState.h"


Enemy::Enemy(const Vector2D& position, Texture* texture, int lives, elementsInfo::elements elem, GameObject* p, bool moving, Vector2D dir, const Scale& scale, float w, GameState* state) : MovingObject(position, texture, dir, scale, state), actualLives(lives), element(elem), player(p) {
	maxLives = lives * 2;  // Representación interna doblada
	actualLives = lives * 2;
	speed = 0.1;

	attackTrigger.x = position.getX() + width; attackTrigger.y = position.getY();
	attackTrigger.w = w; attackTrigger.h = height;
	attackState = normal;

	detectingTrigger.x = position.getX() + width; detectingTrigger.y = position.getY();
	detectingTrigger.w = 2 * w; detectingTrigger.h = height;
	detectPlayer = false;

	movee = moving;
	player = p;
}
Enemy::~Enemy() {

}

void Enemy::Damage(elementsInfo::elements e) {
	cout << "Hit" << endl;
	actualLives -= elementsInfo::matrix[e][element];
	if (actualLives <= 0) Die();
}

void Enemy::Die() {
	dead = true;
	std::cout << "Muerto" << endl;
	deleteMyself();
}

void Enemy::DetectPlayer() {
	SDL_Rect playerRect = player->getRect();
	int frameTime = SDL_GetTicks() - startAttackingTime;
	if (!detectPlayer) {
		if (SDL_HasIntersection(&detectingTrigger, &playerRect)) detectPlayer = true;
		if (detectPlayer) cout << "Detected" << endl;
	}
	else {
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
			if (SDL_HasIntersection(&attackTrigger, &playerRect))
				static_cast<Enemy*>(player)->Damage(element);
			attackState = normal;
		}
	}
}

void Enemy::FollowPlayer() {
	// Distancia de seguridad para comprobar que no se pega al jugador
	if (lookingRight && abs(player->getRect().x - (position.getX() + width)) > nearDistance ||
		!lookingRight && abs(player->getRect().x - position.getX()) > nearDistance) {
		dir = { player->getRect().x - dir.getX(), dir.getY() };
		dir.normalize();
	}
	else {
		dir = { 0, dir.getY() };
		dir.normalize();
	}
}

void Enemy::update() { //Falta el movimiento del enemigo
	if (!movee) {
		return;
	}

	DetectPlayer();
	int frameMovingTime = SDL_GetTicks() - startMovingTime;

	if (lookingRight) // Ajuste del trigger en función del movimiento del enemigo
		attackTrigger.x = position.getX() + width;
	else
		attackTrigger.x = position.getX() - attackTrigger.w;


	attackTrigger.y = position.getY();

	detectingTrigger.x = attackTrigger.x;
	detectingTrigger.y = attackTrigger.y;

	if (!detectPlayer) {
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

	Move();
}

void Enemy::Move() {
	position = position + dir * speed; // No es (position + dir) * speed porque la posición se multiplicaría por la velocidad
	// en vez de que se multiplique solo la dirección, asi que se teletransportaría
}

int Enemy::GetLives() { return actualLives; }

bool Enemy::isDead() { return dead; }