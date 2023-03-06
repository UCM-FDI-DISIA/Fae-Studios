#include "Health.h"
void Health::render() {
	for (int i = 0; i < health; ++i) {
		textures[i]->render(i * textures[i]->width(), 0);
	}
}

void Health::quitHealth() {
	health--;
}

void Health::resetHealth() {
	health = maxHealth;
}

int Health::getHealth() {
	return health;
}
