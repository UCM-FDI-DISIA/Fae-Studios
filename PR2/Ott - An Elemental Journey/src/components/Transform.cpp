#include "Transform.h"

void Transform::update() {
	position = position + velocity; //En cada frame se calcula la nueva posici�n sum�ndole la velocidad
}
