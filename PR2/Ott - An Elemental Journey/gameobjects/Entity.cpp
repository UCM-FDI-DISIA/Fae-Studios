#include "Entity.h"
#include "../gameflow/play/PlayState.h"

bool Entity::recieveDamage(elementsInfo::elements elem) {
	int damageNum = elementsInfo::ottMatrix[elem][currentElement];
	if (damageNum != -1) {
		life -= damageNum;
		if (life <= 0) {
			life = 0; die();
		}
	}
	return dead;
}

void Entity::die() {
	dead = true;
}

bool Entity::isGrounded() { return ground; }

void Entity::useGravity() {
	speed = Vector2D(speed.getX(), speed.getY() + game->Gravity());
}

void Entity::deleteMyself() {
	game->deleteObject(this);
}