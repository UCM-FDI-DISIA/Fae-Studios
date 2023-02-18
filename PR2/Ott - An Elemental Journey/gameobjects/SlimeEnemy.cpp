#include "SlimeEnemy.h"
#include "../gameflow/PlayState.h"

void SlimeEnemy::Move() {
	if (!detectPlayer) {
		int frameMovingTime = SDL_GetTicks() - startMovingTime;
		if (frameMovingTime >= NEW_DIR) {
			dir = { (double)(rand() % 3 - 1), dir.getY() };
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

bool SlimeEnemy::Damage(/*const SDL_Rect& playerAttack,*/ elementsInfo::elements e) { // preguntar a eva como funciona el ataque
	/*if (SDL_HasIntersection(&playerAttack, &damageZone)) {
		cout << "Hit" << endl;
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) {
			Die();
			return true;
		}
		else return false;
	}*/
	return Enemy::Damage(e);
}

void SlimeEnemy::layDownAdjust() { // tener en cuenta dir
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y += height - damageZone.h;
	if (lookingRight) damageZone.x += width - damageZone.w;
}

void SlimeEnemy::getUpAdjust() {
	int aux = damageZone.h;
	damageZone.h = damageZone.w; damageZone.w = aux;
	damageZone.y = position.getY(); damageZone.x = position.getX();
}

void SlimeEnemy::DetectAttackTrigger() {
	if (detectPlayer && player != nullptr || attackState != normal) {
		SDL_Rect playerRect = { 0,0,0,0 };
		 if(player != nullptr) playerRect = player->getRect();
		int frameTime = SDL_GetTicks() - startAttackingTime;
		if (attackState == normal && SDL_HasIntersection(&attackTrigger, &playerRect)) {
			attackState = preparing;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == preparing && frameTime >= PREPARING_TIME) {
			attackState = attacking;
			layDownAdjust();
			getUp = false;
			layDown = true;
			startAttackingTime = SDL_GetTicks();
		}
		else if (attackState == attacking && frameTime >= ATTACKING_TIME) {
			attackState = laying;
			Attack();
		}
		else if (attackState == laying && frameTime >= LAYING_TIME) {
			getUpAdjust();
			layDown = false;
			getUp = true;
			attackState = normal;
		}
	}
}

void SlimeEnemy::update() {
	if (attackState == normal) {
		col = 
	}

	Enemy::update();
}

void SlimeEnemy::Divide() { // generamos dos nuevos slimes 
	// tener en cuenta en constructora y tal que los nuevos slime tndrian menor tamaño y menos vidas
	// tener en cuenta que hay que añadir estos slimes a la lista de gameObjects del estado y eso
	static_cast<PlayState*> (this->getState())->addEnemy(new SlimeEnemy(actualSize--, Vector2D(position.getX() - 10, position.getY()), texture, maxLives - 1, element, player, true, dir, Scale(slimeScale / 1.5, slimeScale / 1.5), 110, 100, this->getState()));
	static_cast<PlayState*> (this->getState())->addEnemy(new SlimeEnemy(actualSize--, Vector2D(position.getX() + 10, position.getY()), texture, maxLives - 1, element, player, true, dir, Scale(slimeScale / 1.5, slimeScale / 1.5), 110, 100, this->getState()));
}

void SlimeEnemy::Die() {
	if(actualSize > 1) Divide();
	Enemy::Die();
}

void SlimeEnemy::render() const{
	texture->renderFrame(getRect(), 0, col);
}