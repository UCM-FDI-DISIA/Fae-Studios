#include "SlimeEnemy.h"

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

bool SlimeEnemy::Damage(const SDL_Rect& playerAttack, elementsInfo::elements e) { // preguntar a eva como funciona el ataque
	if(SDL_HasIntersection(&playerAttack, &damageZone)) Enemy::Damage(e);
	return true; // He añadido esto porque no compilaba, borrar linea
}

void SlimeEnemy::Attack() {

}

void SlimeEnemy::Divide() { // generamos dos nuevos slimes 
	// tener en cuenta en constructora y tal que los nuevos slime tndrian menor tamaño y menos vidas
	// tener en cuenta que hay que añadir estos slimes a la lista de gameObjects del estado y eso

	// He comentado esto porque daba error de compilación
	/*new SlimeEnemy(actualSize--, Vector2D(position.getX(), position.getY()), app->getTexture("enemy", this->getState()->getStateID()), 5, elementsInfo::Earth, player, true, Vector2D(1, 0), Scale(0.5, 0.5), 110, this->getState());*/
}

void SlimeEnemy::Die() {
	if(actualSize > 1) Divide();
	Enemy::Die();
}