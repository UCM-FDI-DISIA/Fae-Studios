#include "Transform.h"

void Transform::update() {
	position = position + velocity; //En cada frame se calcula la nueva posición sumándole la velocidad
}
