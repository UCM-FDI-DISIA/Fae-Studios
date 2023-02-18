#include "Entity.h"
#include "../gameflow/play/PlayState.h"
void Entity::recieveDamage(int elem) {
	int damageNum = elementsInfo[elem][currentElement];
	if (damageNum != -1) {
		life -= damageNum;
		if (life <= 0) die();
	}
}
void Entity::die() {
	
}

bool Entity::isGrounded() { return ground; }

void Entity::useGravity() {
	speed = Vector2D(speed.getX(), speed.getY() + game->Gravity());
}

void Entity::deleteMyself() {
	game->deleteObject(this);
}