#include "SlimeEnemy.h"
#include "../gameflow/play/PlayState.h"

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

	if(attackState != attacking && attackState != laying)
		Enemy::Move();
}

bool SlimeEnemy::recieveDamage(/*const SDL_Rect& playerAttack,*/ elementsInfo::elements e) { // preguntar a eva como funciona el ataque
	/*if (SDL_HasIntersection(&playerAttack, &damageZone)) {
		cout << "Hit" << endl;
		actualLives -= elementsInfo::matrix[e][element];
		if (actualLives <= 0) {
			Die();
			return true;
		}
		else return false;
	}*/
	return Enemy::recieveDamage(e);
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
	if (!dead) {
		if (attackState == normal) {
			col = (SDL_GetTicks() / time_per_frame) % 4;
		}
		else if (attackState == preparing) {
			col = (SDL_GetTicks() / time_per_frame) % 4;
			timer = SDL_GetTicks();
		}
		else if (attackState == attacking) {
		
			if (col != 10)  col = 4 + ((SDL_GetTicks() - timer) / time_per_frame) % 7;
		}
		else if (attackState == laying) {
			int frameTime = SDL_GetTicks() - startAttackingTime;
			if (frameTime < 2000) { col = 10; timer = SDL_GetTicks(); }
			else {
				if (col != 16) col = 10 + ((SDL_GetTicks() - timer) / time_per_frame) % 7;
			}
		}
	}
	else {
		if (col != 21)  col = 17 + ((SDL_GetTicks() - timer) / time_per_frame) % 22;
		else {
			if (actualSize > 1) Divide(); 
			deleteMyself();
		}
	}
	Enemy::update();
	fil = 0;
}

void SlimeEnemy::Divide() { // generamos dos nuevos slimes 
	// tener en cuenta en constructora y tal que los nuevos slime tndrian menor tamaño y menos vidas
	// tener en cuenta que hay que añadir estos slimes a la lista de gameObjects del estado y eso
	game->addEntity(new SlimeEnemy(actualSize - 1, Vector2D(position.getX() - 40, position.getY()), texture, maxLives / 2 - 1, element, player, true, dir, Scale(slimeScale / 1.5, slimeScale / 1.5), 110, 100, game, colliderRender));
	game->addEntity(new SlimeEnemy(actualSize - 1, Vector2D(position.getX() + 40, position.getY()), texture, maxLives / 2 - 1, element, player, true, dir, Scale(slimeScale / 1.5, slimeScale / 1.5), 110, 100, game, colliderRender));
}

void SlimeEnemy::die() {
	Enemy::die();
}

void SlimeEnemy::render(const SDL_Rect& Camera) const{
	SDL_Rect thisRect = getRect();
	thisRect.x -= Camera.x;
	thisRect.y -= Camera.y;
	texture->renderFrame(thisRect, fil, col, 0, flip[!lookingRight]);
	Enemy::render(Camera);
}