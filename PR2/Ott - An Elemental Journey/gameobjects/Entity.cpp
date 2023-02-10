#include "Entity.h"
void Entity::recieveDamage(int elem) {
	int damageNum = elementsInfo[elem][currentElement];
	if (damageNum != -1) {
		life -= damageNum;
		if (life <= 0) die();
	}
}
void Entity::die() {
	
}